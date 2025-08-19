#include "spdlog/spdlog.h"
#include <gtest/gtest.h>

#include "SmartHouse/Logging/Stm32/LogManager.h"
#include "SmartHouse/Logging/Stm32/MemoryLogSink.h"
#include "SmartHouse/Logging/Stm32/FuncLogSink.h"
#include "SmartHouse/Logging/Stm32/DummyDebuggerDetector.h"
#include "SmartHouse/Logging/Stm32/LogLevel.h"
#include "SmartHouse/Logging/Stm32/Logger.h"
#include "MockTimestampProvider.h"

namespace LogNs = SmartHouse::Logging::Stm32;
using LogManagerMemory = LogNs::LogManager<LogNs::MemoryLogSink, LogNs::MockTimestampProvider>;
using LogManagerFunc = LogNs::LogManager<LogNs::FuncLogSink<[](uint8_t c) {return 0; }>, LogNs::MockTimestampProvider>;

TEST(LogManagerTest, TestGetName)
{
	auto logger = LogNs::Logger<LogManagerMemory>("general");
	EXPECT_EQ(logger.GetName(), "general");
}

TEST(LogManagerTest, TestInfo)
{
	LogManagerMemory::GetLogSinkRef().ClearLog();
	auto logger = LogNs::Logger<LogManagerMemory>("general");
	logger.Info("Hello %s", "World!");
	std::string actualLog = LogManagerMemory::GetLogSinkRef().GetLog();
	EXPECT_EQ(actualLog, "[general] [0] [info] Hello World!");
}

TEST(LogManagerTest, TestError)
{
	LogManagerMemory::GetLogSinkRef().ClearLog();
	auto logger = LogNs::Logger<LogManagerMemory>("general");
	logger.Error("Hello %3.2f!", 123.45);
	std::string actualLog = LogManagerMemory::GetLogSinkRef().GetLog();
	EXPECT_EQ(actualLog, "[general] [0] [error] Hello 123.45!");
}

TEST(LogManagerTest, TestDebug)
{
	LogManagerMemory::GetLogSinkRef().ClearLog();
	auto logger = LogNs::Logger<LogManagerMemory>("general");
	logger.Debug("Hello %d!", 123);
	std::string actualLog = LogManagerMemory::GetLogSinkRef().GetLog();
	EXPECT_EQ(actualLog, "");
}

TEST(LogManagerTest, TestFunc)
{
	auto logger = LogNs::Logger<LogManagerFunc>("general");
	logger.Debug("Hello %d!", 123);
}