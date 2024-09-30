#include "Logging.h"
#include "spdlog/spdlog.h"
#include <boost/test/unit_test.hpp>
#include "LogManager.h"
#include "LogSinkMemBuf.h"

BOOST_AUTO_TEST_SUITE(LogManagerTestSuit)

BOOST_AUTO_TEST_CASE(TestGetLogger)
{
	auto logger = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::LogSinkMemBuf>::GetLogger("general");
	BOOST_CHECK(logger.GetName() == "general");
}

BOOST_AUTO_TEST_CASE(TestLoggerLog)
{
	auto logger = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::LogSinkMemBuf>::GetLogger("general");
	auto& logManager = logger.GetLogManager();
	auto& sink = logManager.GetSinkRef();

	logger.Info("My name is %s and I am %d years old", "John Doe", 56);
	BOOST_CHECK(sink.GetMessageBuffer().size() == 1);

	spdlog::info("Logger message: {}", sink.GetMessageBuffer()[0]);

	BOOST_CHECK(sink.GetMessageBuffer()[0] == "My name is John Doe and I am 56 years old");

}

BOOST_AUTO_TEST_SUITE_END()