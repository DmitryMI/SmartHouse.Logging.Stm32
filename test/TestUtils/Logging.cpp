#include "Logging.h"
#include "spdlog/spdlog.h"

void TestUtils::Logging::Setup(std::string_view LoggerName)
{
	auto old_default_logger = spdlog::default_logger();
	auto new_default_logger = old_default_logger->clone(static_cast<std::string>(LoggerName));
	spdlog::set_default_logger(new_default_logger);

	spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] %v");
}
