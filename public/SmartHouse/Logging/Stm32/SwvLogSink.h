#pragma once

#include <cstdint>

#ifdef _MSC_VER
#include <stdio.h>
using USART_TypeDef = void*;
#define ITM_SendChar(ch); printf("%c", ch);
#endif

namespace SmartHouse::Logging::Stm32
{
	class SwvLogSink
	{
	public:
		void Send(uint8_t c)
		{
			ITM_SendChar(c);
		}
	};
}