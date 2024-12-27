#pragma once

#include <cstdint>

#ifdef _MSC_VER
	#include <stdio.h>
	using UART_HandleTypeDef = uint64_t;
	#define HAL_UART_Transmit(instance, buffer, data, timeout) printf("%s\n", buffer);
#endif

namespace SmartHouse::Logging::Stm32
{
	template<UART_HandleTypeDef* TUsartInstance, int TTimeout = 1000>
	class UartLogSink
	{
	public:
		void Send(uint8_t c)
		{
			HAL_UART_Transmit(&huart1, (const uint8_t*)c, 1, TTimeout);
		}
	};
}
