#pragma once

#include "Logger.h"
#include <memory>
#include <string>
#include "LogLevel.h"
#include <stdarg.h>
#include <array>
#include "TickTimestampProvider.h"
#include "DummyDebuggerDetector.h"

namespace SmartHouse::Logging::Stm32
{
	template<typename TLogSink, typename TTimestampProvider = TickTimestampProvider<>, typename TDebuggerDetector = DummyDebuggerDetector<true>, LogLevel::Level TMinLevel = LogLevel::Level::Info, int TMaxLogMessageSize = 80>
	class LogManager
	{
	public:
		static constexpr int OuterFormatExtraSize = 56;
		static constexpr int LoggerNameMaxLength = 12;

		static LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize>& GetInstanceRef()
		{
			return Instance;
		}

		static void SetInstance(const LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize>& logManager)
		{
			Instance = logManager;
		}

		static void SetInstanceMove(LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize>& logManager)
		{
			Instance = std::move(logManager);
		}

		template<LogLevel::Level TLoggerLevel = TMinLevel>
		Logger<TLoggerLevel, LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize>> GetLogger(std::string_view loggerName)
		{
			return Logger<TLoggerLevel, LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize>>(loggerName, *this);
		}

		template<LogLevel::Level TMessageLevel>
		void Log(std::string_view loggerName, const char* format, va_list args)
		{
			if constexpr (static_cast<uint8_t>(TMessageLevel) < static_cast<uint8_t>(TMinLevel))
			{
				return;
			}

			LogInternal<TMessageLevel>(loggerName, format, args);
		}

		TLogSink& GetSinkRef()
		{
			return m_Sink;
		}

		TTimestampProvider& GetTimestampProviderRef()
		{
			return m_TimestampProvider;
		}

		TDebuggerDetector& GetDebuggerDetectorRef()
		{
			return m_DebuggerDetector;
		}

	private:
		static LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize> Instance;

		TLogSink m_Sink;
		TTimestampProvider m_TimestampProvider;
		TDebuggerDetector m_DebuggerDetector;

		template<LogLevel::Level TMessageLevel>
		void LogInternal(std::string_view loggerName, const char* format, va_list args)
		{
			if (!m_DebuggerDetector.IsDebuggerPresent())
			{
				return;
			}

			int outerMessageSize = 0;

			std::array<char, TMaxLogMessageSize + 1> logInnerBuffer;
			std::array<char, OuterFormatExtraSize + TMaxLogMessageSize + 1> logOuterBuffer;

			int loggerNamePadding = (LoggerNameMaxLength - (int)loggerName.size()) / 2;
			if (loggerNamePadding < 0)
			{
				loggerNamePadding = 0;
			}
			int loggerNameExtraPadding = (int)loggerName.size() % 2 == 0 ? 0 : 1;

			constexpr std::string_view levelStr = LogLevel::ToString(TMessageLevel);
			constexpr int levelMaxLength = LogLevel::GetMaxLevelNameLength();
			constexpr int levelPadding = (levelMaxLength - (int)levelStr.size()) / 2;
			constexpr int levelExtraPadding = (int)levelStr.size() % 2 == 0 ? 0 : 1;

#ifdef _MSC_VER
			int innerMessageSize = vsprintf_s(logInnerBuffer.data(), logInnerBuffer.size(), format, args);
			if (innerMessageSize <= 0)
			{
				return;
			}
			
			outerMessageSize = sprintf_s(logOuterBuffer.data(), logOuterBuffer.size(),
				"[%s] [%*s%s%*s] [%*s%s%*s] %s\n", 
				m_TimestampProvider.GetTimestampString().c_str(),
				loggerNamePadding + loggerNameExtraPadding, "", loggerName.data(), loggerNamePadding, "",
				levelPadding + levelExtraPadding, "", levelStr.data(), levelPadding, "",
				logInnerBuffer.data()
			);

			if (outerMessageSize <= 0)
			{
				return;
			}
#elif defined(__GNUC__)

			int innerMessageSize = vsprintf(logInnerBuffer.data(), format, args);
			if (innerMessageSize <= 0)
			{
				return;
			}

			outerMessageSize = sprintf(logOuterBuffer.data(), "[%s] [%*s%s%*s] [%*s%s%*s] %s\n",
					m_TimestampProvider.GetTimestampString().c_str(),
					loggerNamePadding + loggerNameExtraPadding, "", loggerName.data(), loggerNamePadding, "",
					levelPadding + levelExtraPadding, "", levelStr.data(), levelPadding, "",
					logInnerBuffer.data()
			);

			if (outerMessageSize <= 0)
			{
				return;
			}

#else
#error "This compiler is not supported!"
#endif
			m_Sink.Send(logOuterBuffer.data(), outerMessageSize);
		}
	};

	template<typename TLogSink, typename TTimestampProvider, typename TDebuggerDetector, LogLevel::Level TMinLevel, int TMaxLogMessageSize>
	LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize> LogManager<TLogSink, TTimestampProvider, TDebuggerDetector, TMinLevel, TMaxLogMessageSize>::Instance;
}
