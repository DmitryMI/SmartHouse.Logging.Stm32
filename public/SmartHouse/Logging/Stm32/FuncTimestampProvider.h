#pragma once

#include <cstdint>

namespace SmartHouse::Logging::Stm32
{
	template<auto Func>
	class FuncTimestampProvider
	{
	public:
		uint32_t GetTimestamp()
		{
			return Func();
		}
	};
}