#pragma once

#ifdef _MSC_VER
	#include <stdio.h>
	using UART_HandleTypeDef = uin64_t;
	#define HAL_UART_Transmit(instance, buffer, data, timeout) printf("%s\n", buffer);
#endif

namespace SmartHouse::Logging::Stm32
{
	template<UART_HandleTypeDef* TUsartInstance, int TTimeout = 1000>
	class UartLogSink
	{
	public:
		void Send(const char* buffer, size_t size)
		{
			HAL_UART_Transmit(&huart1, (const uint8_t*)buffer, size, TTimeout);
		}
	};
}
