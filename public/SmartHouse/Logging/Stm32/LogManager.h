#pragma once

#include <cstdio>
#include <string_view>
#include "DummyDebuggerDetector.h"
#include "LogLevel.h"
#include "TickTimestampProvider.h"
#include <functional>

#ifndef __GNUC__
#include <array>
#endif

namespace SmartHouse::Logging::Stm32
{
	extern std::function<void(uint8_t)> LogManagerPutCharCallback;

	template<typename TLogSink, typename TTimestampProvider = TickTimestampProvider, typename TDebuggerDetector = DummyDebuggerDetector<true>, LogLevel::Level TMinLevel = LogLevel::Level::Info>
	class LogManager
	{
	public:

		static void Init()
		{
			LogManagerPutCharCallback = PutCharCallback;
		}

		template<LogLevel::Level TMessageLevel>
		static void Log(std::string_view loggerName, const char* format, va_list args)
		{
			if constexpr (static_cast<uint8_t>(TMessageLevel) < static_cast<uint8_t>(TMinLevel))
			{
				return;
			}

			if (!m_DebuggerDetector.IsDebuggerPresent())
			{
				return;
			}

#ifdef __GNUC__
			printf("[%s] [%lu] [%s] ", loggerName.data(), m_TimestampProvider.GetTimestamp(), LogLevel::ToString(TMessageLevel).data());
			vprintf(format, args);
#else
			std::array<char, 256> buffer;
			char* bufferPtr = buffer.data();
			size_t pos = 0;
			pos += snprintf(bufferPtr, buffer.size(), "[%s] [%u] [%s] ", loggerName.data(), m_TimestampProvider.GetTimestamp(), LogLevel::ToString(TMessageLevel).data());
			pos += vsnprintf(bufferPtr + pos, buffer.size() - pos, format, args);
			for (size_t i = 0; i < pos; i++)
			{
				PutCharCallback(buffer[i]);
			}
#endif
			
			PutCharCallback('\n');
		}

		static TDebuggerDetector& GetDebuggerDetectorRef()
		{
			return m_DebuggerDetector;
		}

		static TLogSink& GetLogSinkRef()
		{
			return m_LogSink;
		}

		static void PutCharCallback(uint8_t c)
		{
			m_LogSink.Send(c);
		}

	private:
		static TDebuggerDetector m_DebuggerDetector;
		static TLogSink m_LogSink;
		static TTimestampProvider m_TimestampProvider;
	};


	template<typename TLogSink, typename TTimestampProvider, typename TDebuggerDetector, LogLevel::Level TMinLevel>
	TDebuggerDetector LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel>::m_DebuggerDetector;

	template<typename TLogSink, typename TTimestampProvider, typename TDebuggerDetector, LogLevel::Level TMinLevel>
	TLogSink LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel>::m_LogSink;

	template<typename TLogSink, typename TTimestampProvider, typename TDebuggerDetector, LogLevel::Level TMinLevel>
	TTimestampProvider LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel>::m_TimestampProvider;
}