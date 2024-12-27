#pragma once

#include <cstdint>

#ifdef _MSC_VER
#include <Windows.h>
#include <sysinfoapi.h>
#define HAL_GetTick() static_cast<uint32_t>(GetTickCount64());
#else
#include "main.h"
#endif

namespace SmartHouse::Logging::Stm32
{
	class TickTimestampProvider
	{
	public:
		uint32_t GetTimestamp()
		{
			return HAL_GetTick();
		}
	};
}