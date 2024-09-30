#pragma once

#ifdef _MSC_VER
#include <stdio.h>
using USART_TypeDef = void*
#define ITM_SendChar(ch); printf("%c", ch);
#endif

namespace SmartHouse::Logging::Stm32
{
	class LogSinkSerialWire
	{
	public:
		void Send(const char* buffer, size_t size)
		{
			for (size_t i = 0; i < size; i++)
			{
				ITM_SendChar(buffer[i]);
			}
		}
	};
}