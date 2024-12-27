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

BOOST_AUTO_TEST_CASE(TestLog)
{
	auto logger = LogNs::Logger<LogManagerType>("general");
	logger.Info("Hello %s\n", "World!");
	std::string actualLog = LogManagerType::GetLogSinkRef().GetLog();
	BOOST_CHECK(actualLog == "[general] [0] Hello World!\n");
}

BOOST_AUTO_TEST_SUITE_END()