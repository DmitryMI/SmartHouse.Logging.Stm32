#pragma once

#include "LogLevel.h"
#include <string>
#include <stdio.h>

namespace SmartHouse::Logging::Stm32
{
	template<LogLevel::Level TLevel>
	class Logger
	{
	public:
		Logger(const std::string& name)
		{
			m_Name = name;
		}

		template<LogLevel::Level TMessageLevel>
		void Log(const char* format, ...) const
		{
			if constexpr(static_cast<uint8_t>(TMessageLevel) < static_cast<uin8_t>(TLevel))
			{
				return;
			}


		}
		
		void Debug(const char* format, ...) const;
		void Info(const char* format, ...) const;
		void Warn(const char* format, ...) const;
		void Error(const char* format, ...) const;
		void Critical(const char* format, ...) const;

	private:
		std::string m_Name;
	};
}
