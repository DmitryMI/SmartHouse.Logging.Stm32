#pragma once

#include "Logger.h"
#include <memory>
#include <string>
#include "LogLevel.h"
#include <stdarg.h>
#include <array>

namespace SmartHouse::Logging::Stm32
{
	template<typename TLogSink, LogLevel::Level TMinLevel = LogLevel::Level::Info, int TMaxLogMessageSize = 256>
	class LogManager
	{
	public:
		const int LoggerNameMaxLength = 12;

		static LogManager<TLogSink, TMinLevel, TMaxLogMessageSize>& GetInstanceRef()
		{
			return Instance;
		}

		template<LogLevel::Level TLoggerLevel = TMinLevel>
		static Logger<TLoggerLevel, LogManager<TLogSink, TMinLevel, TMaxLogMessageSize>> GetLogger(std::string_view loggerName)
		{
			return GetInstanceRef().GetLoggerInternal(loggerName);
		}

		template<LogLevel::Level TMessageLevel>
		static void Log(std::string_view loggerName, const char* format, va_list args)
		{
			if constexpr (static_cast<uint8_t>(TMessageLevel) < static_cast<uint8_t>(TMinLevel))
			{
				return;
			}

			GetInstanceRef().LogInternal<TMessageLevel>(loggerName, format, args);
		}

		TLogSink& GetSinkRef()
		{
			return m_Sink;
		}

	private:
		static LogManager<TLogSink, TMinLevel, TMaxLogMessageSize> Instance;

		TLogSink m_Sink;

		template<LogLevel::Level TLoggerLevel = TMinLevel>
		Logger<TLoggerLevel, LogManager<TLogSink, TMinLevel, TMaxLogMessageSize>> GetLoggerInternal(std::string_view loggerName)
		{
			return Logger<TLoggerLevel, LogManager<TLogSink, TMinLevel, TMaxLogMessageSize>>(loggerName);
		}

		template<LogLevel::Level TMessageLevel>
		void LogInternal(std::string_view loggerName, const char* format, va_list args)
		{
			std::array<char, TMaxLogMessageSize + 1> logInnerBuffer;
			std::array<char, TMaxLogMessageSize + 1> logOuterBuffer;
			
			const int loggerNamePadding = (LoggerNameMaxLength - loggerName.size()) / 2;

			const std::string_view levelStr = LogLevel::ToString(TMessageLevel);
			const int levelMaxLength = LogLevel::GetMaxLevelNameLength();
			const int levelPadding = (levelMaxLength - levelStr.size()) / 2;

#ifdef _MSC_VER
			int innerMessageSize = vsprintf_s(logInnerBuffer.data(), logInnerBuffer.size(), format, args);
			
			int outerMessageSize = sprintf_s(logOuterBuffer.data(), logOuterBuffer.size(), 
				"[%s] [%*s%s%*s] [%*s%s%*s] %s\n", 
				GetFormattedTime().c_str(), 
				loggerNamePadding, " ", loggerName.data(), loggerNamePadding, " ",
				levelPadding, " ", levelStr.data(), levelPadding, " ",
				logInnerBuffer.data()
			);
#else
#error "This compiler is not supported!"
#endif
			m_Sink.Send(logOuterBuffer.data(), outerMessageSize);
		}		

		std::string GetFormattedTime() const
		{
			return "000";
		}
	};

	template<typename TLogSink, LogLevel::Level TMinLevel, int TMaxLogMessageSize>
	LogManager<TLogSink, TMinLevel, TMaxLogMessageSize> LogManager<TLogSink, TMinLevel, TMaxLogMessageSize>::Instance;
}
