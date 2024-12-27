#pragma once

#include <cstdint>

namespace SmartHouse::Logging::Stm32
{
	class MockTimestampProvider
	{
	public:
		uint32_t GetTimestamp()
		{
			return 0;
		}
	};
}