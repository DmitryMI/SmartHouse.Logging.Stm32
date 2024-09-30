#pragma once

#ifdef _MSC_VER
	#include <stdio.h>
	using USART_TypeDef = void*;
	#define HAL_UART_Transmit(instance, buffer, data, timeout) printf("%s\n", buffer);
#endif

namespace SmartHouse::Logging::Stm32
{
	template<USART_TypeDef TUsartInstance, int TTimeout = 1000>
	class LogSinkUart
	{
	public:
		void Send(const char* buffer, size_t size)
		{
			HAL_UART_Transmit(&huart1, buffer, size, TTimeout);
		}
	};
}