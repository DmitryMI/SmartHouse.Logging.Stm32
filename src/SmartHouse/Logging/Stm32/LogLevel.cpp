/*
 * LogLevel.cpp
 *
 *  Created on: Sep 30, 2024
 *      Author: DmitriyPC
 */

#include "LogLevel.h"
#include <algorithm>

namespace SmartHouse::Logging::Stm32
{
	std::string LogLevel::ToString(LogLevel::Level enumValue)
	{
		switch(enumValue)
		{
		case LogLevel::Level::Debug:
			return "Debug";
		case LogLevel::Level::Info:
			return "Info";
		case LogLevel::Level::Warn:
			return "Warn";
		case LogLevel::Level::Error:
			return "Error";
		case LogLevel::Level::Critical:
			return "Critical";
		case LogLevel::Level::NoLevel:
			return "NoLevel";
		}

		return "NoLevel";
	}

	LogLevel::Level LogLevel::FromString(std::string_view strValue)
	{
		std::string str = strValue;
		std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
		{
			return std::tolower(c);
		});

		if (str == "debug")
		{
			return LogLevel::Level::Debug;
		}
		else if (str == "info")
		{
			return LogLevel::Level::Info;
		}
		else if (str == "warn")
		{
			return LogLevel::Level::Warn;
		}
		else if (str == "error")
		{
			return LogLevel::Level::Error;
		}
		else if (str == "critical")
		{
			return LogLevel::Level::Critical;
		}

		return LogLevel::Level::NoLevel;
	}

}
