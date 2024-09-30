#include "Logging.h"
#include "spdlog/spdlog.h"
#include <boost/test/unit_test.hpp>
#include "LogManager.h"
#include "MemBufLogSink.h"
#include "CounterTimestampProvider.h"

BOOST_AUTO_TEST_SUITE(LogManagerTestSuit)

BOOST_AUTO_TEST_CASE(TestGetLogger)
{
	auto logManager = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::MemBufLogSink, SmartHouse::Logging::Stm32::CounterTimestampProvider>();
	auto logger = logManager.GetLogger("general");
	BOOST_CHECK(logger.GetName() == "general");
}

BOOST_AUTO_TEST_CASE(TestLoggerDebug)
{
	auto logManager = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::MemBufLogSink, SmartHouse::Logging::Stm32::CounterTimestampProvider>();
	auto logger = logManager.GetLogger("general");
	auto& sink = logManager.GetSinkRef();

	logger.Debug("My name is %s and I am %d years old", "John Doe", 56);
	BOOST_CHECK(sink.GetMessageBuffer().size() == 0);
}


BOOST_AUTO_TEST_CASE(TestLoggerInfo)
{
	auto logManager = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::MemBufLogSink, SmartHouse::Logging::Stm32::CounterTimestampProvider>();
	auto logger = logManager.GetLogger("SomeName");
	auto& sink = logManager.GetSinkRef();

	logger.Info("My name is %s and I am %d years old", "John Doe", 56);
	BOOST_CHECK(sink.GetMessageBuffer().size() == 1);

	spdlog::info("Logger message: {}", sink.GetMessageBuffer()[0]);

	BOOST_CHECK(sink.GetMessageBuffer()[0] == "[0] [  SomeName  ] [  info  ] My name is John Doe and I am 56 years old\n");
}

BOOST_AUTO_TEST_CASE(TestLoggerWarn)
{
	auto logManager = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::MemBufLogSink, SmartHouse::Logging::Stm32::CounterTimestampProvider>();
	auto logger = logManager.GetLogger("general");
	auto& sink = logManager.GetSinkRef();

	logger.Warn("My name is %s and I am %d years old", "John Doe", 56);
	BOOST_CHECK(sink.GetMessageBuffer().size() == 1);

	spdlog::info("Logger message: {}", sink.GetMessageBuffer()[0]);

	BOOST_CHECK(sink.GetMessageBuffer()[0] == "[0] [   general  ] [  warn  ] My name is John Doe and I am 56 years old\n");
}

BOOST_AUTO_TEST_CASE(TestLoggerError)
{
	auto logManager = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::MemBufLogSink, SmartHouse::Logging::Stm32::CounterTimestampProvider>();
	auto logger = logManager.GetLogger("AnotherName");
	auto& sink = logManager.GetSinkRef();

	logger.Error("My name is %s and I am %d years old", "John Doe", 56);
	BOOST_CHECK(sink.GetMessageBuffer().size() == 1);

	spdlog::info("Logger message: {}", sink.GetMessageBuffer()[0]);

	BOOST_CHECK(sink.GetMessageBuffer()[0] == "[0] [ AnotherName] [  error ] My name is John Doe and I am 56 years old\n");
}

BOOST_AUTO_TEST_CASE(TestLoggerCritical)
{
	auto logManager = SmartHouse::Logging::Stm32::LogManager<SmartHouse::Logging::Stm32::MemBufLogSink, SmartHouse::Logging::Stm32::CounterTimestampProvider>();
	auto logger = logManager.GetLogger("1234");
	auto& sink = logManager.GetSinkRef();

	logger.Critical("My name is %s and I am %d years old", "John Doe", 56);
	BOOST_CHECK(sink.GetMessageBuffer().size() == 1);

	spdlog::info("Logger message: {}", sink.GetMessageBuffer()[0]);

	BOOST_CHECK(sink.GetMessageBuffer()[0] == "[0] [    1234    ] [critical] My name is John Doe and I am 56 years old\n");
}


BOOST_AUTO_TEST_SUITE_END()