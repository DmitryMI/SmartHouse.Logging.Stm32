#include "spdlog/spdlog.h"
#include <boost/test/unit_test.hpp>

#include "SmartHouse/Logging/Stm32/LogManager.h"
#include "SmartHouse/Logging/Stm32/MemoryLogSink.h"
#include "SmartHouse/Logging/Stm32/DummyDebuggerDetector.h"
#include "SmartHouse/Logging/Stm32/LogLevel.h"
#include "SmartHouse/Logging/Stm32/Logger.h"
#include "MockTimestampProvider.h"

namespace LogNs = SmartHouse::Logging::Stm32;
using LogManagerType = LogNs::LogManager<LogNs::MemoryLogSink, LogNs::MockTimestampProvider>;

BOOST_AUTO_TEST_SUITE(LogManagerTestSuit)

BOOST_AUTO_TEST_CASE(TestGetName)
{
	auto logger = LogNs::Logger<LogManagerType>("general");
	BOOST_CHECK(logger.GetName() == "general");
}

BOOST_AUTO_TEST_CASE(TestInfo)
{
	LogManagerType::GetLogSinkRef().ClearLog();
	auto logger = LogNs::Logger<LogManagerType>("general");
	logger.Info("Hello %s\n", "World!");
	std::string actualLog = LogManagerType::GetLogSinkRef().GetLog();
	BOOST_CHECK(actualLog == "[general] [0] [info] Hello World!\n");
}

BOOST_AUTO_TEST_CASE(TestError)
{
	LogManagerType::GetLogSinkRef().ClearLog();
	auto logger = LogNs::Logger<LogManagerType>("general");
	logger.Error("Hello %3.2f!\n", 123.45);
	std::string actualLog = LogManagerType::GetLogSinkRef().GetLog();
	BOOST_CHECK(actualLog == "[general] [0] [error] Hello 123.45!\n");
}

BOOST_AUTO_TEST_CASE(TestDebug)
{
	LogManagerType::GetLogSinkRef().ClearLog();
	auto logger = LogNs::Logger<LogManagerType>("general");
	logger.Debug("Hello %d!\n", 123);
	std::string actualLog = LogManagerType::GetLogSinkRef().GetLog();
	BOOST_CHECK(actualLog == "");
}

BOOST_AUTO_TEST_SUITE_END()