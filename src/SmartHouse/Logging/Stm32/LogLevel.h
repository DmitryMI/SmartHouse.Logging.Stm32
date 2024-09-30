#pragma once

#include <string>
#include <string_view>
#include <stdint.h>

namespace SmartHouse::Logging::Stm32
{
	class LogLevel
	{
	public:
		enum class Level : uin8_t
		{
			NoLevel = 0,
			Debug = 1,
			Info = 2,
			Warn = 3,
			Error = 4,
			Critical = 5
		};

		static std::string ToString(Level enumValue);
		static Level FromString(std::string_view strValue);
	}

}
