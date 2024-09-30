#pragma once

#include "Logger.h"
#include "main.h"
#include <memory>
#include <string>
#include "LogLevel.h"

namespace SmartHouse::Logging::Stm32
{
	template<int TMaxLogMessageSize = 256>
	class LogManager
	{
	public:
		static std::shared_ptr<Logger> GetLogger(std::string_view loggerName, LogLevel::Level level);

	private:
		std::shared_ptr<Logger> GetLogger(std::string_view loggerName, LogLevel::Level level);

		std::unique_ptr<LogManager> Instance = nullptr;
	};
}
