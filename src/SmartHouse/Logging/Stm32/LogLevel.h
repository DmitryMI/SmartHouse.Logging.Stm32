#pragma once

#include <string>
#include <string_view>
#include <stdint.h>
#include <algorithm>

namespace SmartHouse::Logging::Stm32
{
	class LogLevel
	{
	public:
		enum class Level : uint8_t
		{
			NoLevel = 0,
			Debug = 1,
			Info = 2,
			Warn = 3,
			Error = 4,
			Critical = 5,
			MAX
		};

		static consteval int GetMaxLevelNameLength()
		{
			int maxLen = 0;
			const uint8_t maxLevelEnum = static_cast<uint8_t>(Level::MAX);
			for (uint8_t i = 0; i < maxLevelEnum; i++)
			{
				const Level level = static_cast<Level>(i);
				const int len = ToString(level).size();
				if (maxLen < len)
				{
					maxLen = len;
				}
			}

			return maxLen;
		}

		static constexpr std::string_view ToString(Level enumValue)
		{
			switch (enumValue)
			{
			case LogLevel::Level::Debug:
				return "debug";
			case LogLevel::Level::Info:
				return "info";
			case LogLevel::Level::Warn:
				return "warn";
			case LogLevel::Level::Error:
				return "error";
			case LogLevel::Level::Critical:
				return "critical";
			case LogLevel::Level::NoLevel:
				return "nolevel";
			}

			return "nolevel";
		}

		static constexpr Level FromString(std::string_view strValue)
		{
			std::string str = std::string(strValue);
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

	};
}
