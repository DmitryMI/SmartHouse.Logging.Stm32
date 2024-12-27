#pragma once

#include <string>
#include <string_view>
#include <stdio.h>
#include <stdarg.h>

namespace SmartHouse::Logging::Stm32
{
	template<typename TLogManagerType>
	class Logger
	{
	public:
		Logger(std::string_view name) : m_Name(name)
		{
			TLogManagerType::Init();
		}

		std::string_view GetName() const
		{
			return m_Name;
		}

		template<LogLevel::Level TMessageLevel>
		void Log(const char* format, ...) const
		{
			va_list argptr;
			va_start(argptr, format);
			LogInternal<TMessageLevel>(format, argptr);
			va_end(argptr);
		}

		void Debug(const char* format, ...) const
		{
			va_list argptr;
			va_start(argptr, format);
			LogInternal<LogLevel::Level::Debug>(format, argptr);
			va_end(argptr);
		}

		void Info(const char* format, ...) const
		{
			va_list argptr;
			va_start(argptr, format);
			LogInternal<LogLevel::Level::Info>(format, argptr);
			va_end(argptr);
		}

		void Warn(const char* format, ...) const
		{
			va_list argptr;
			va_start(argptr, format);
			LogInternal<LogLevel::Level::Warn>(format, argptr);
			va_end(argptr);
		}

		void Error(const char* format, ...) const
		{
			va_list argptr;
			va_start(argptr, format);
			LogInternal<LogLevel::Level::Error>(format, argptr);
			va_end(argptr);
		}

		void Critical(const char* format, ...) const
		{
			va_list argptr;
			va_start(argptr, format);
			LogInternal<LogLevel::Level::Critical>(format, argptr);
			va_end(argptr);
		}

	private:
		std::string_view m_Name;

		template<LogLevel::Level TMessageLevel>
		void LogInternal(const char* format, va_list args) const
		{
			TLogManagerType::template Log<TMessageLevel>(m_Name, format, args);
		}
	};
}
