#include "Logging.h"
#include "spdlog/spdlog.h"
#include "SmallFormatter.h"
#include <boost/test/unit_test.hpp>
#include <array>

BOOST_AUTO_TEST_SUITE(SmallFormatterTestSuit)

namespace LogNs = SmartHouse::Logging::Stm32;

BOOST_AUTO_TEST_CASE(TestInteger)
{
	LogNs::SmallFormatter formatter;
	const char* format = "%d %3.2f %+3d %s %d %x";
	std::array<char, 100> buffer;
	int resultCharNum = formatter.AsSnprintf(buffer.data(), buffer.size(), format, -12, 13.96f, 14, "STRING", 15, 16);
	std::string resultString = std::string(buffer.data());
	std::array<char, 100> expectedResultBuffer;
	sprintf_s(expectedResultBuffer.data(), expectedResultBuffer.size(), format, -12, 13.96f, 14, "STRING", 15, 16);
	std::string expectedResult = std::string(expectedResultBuffer.data());

	spdlog::info("SmallFormat result: '{}'", resultString);
	spdlog::info("sprintf result: '{}'", expectedResult);
	BOOST_CHECK(resultString == expectedResult);
}


BOOST_AUTO_TEST_SUITE_END()