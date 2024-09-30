#pragma once

#ifdef _MSC_VER
#include <Windows.h>
#include <sysinfoapi.h>
#define HAL_GetTick() GetTickCount64();
#endif

#include <string>
#include <sstream>
#include <iomanip>

namespace SmartHouse::Logging::Stm32
{
	template<int FieldSize = 12>
	class TickTimestampProvider
	{
	public:
		std::string GetTimestampString()
		{
			std::stringstream stringBuilder;
			stringBuilder << std::right << std::setw(FieldSize) << HAL_GetTick();
			return stringBuilder.str();
		}
	};
}