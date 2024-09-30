#pragma once

#include <stdint.h>

#ifdef _MSC_VER
	using GPIO_TypeDef = uint64_t;
	#define HAL_GPIO_ReadPin(port, pin) (0);
#endif


namespace SmartHouse::Logging::Stm32
{
	template<uint32_t TGpio, uint16_t TPin, int TDetectionLevel = 0>
	class GpioDebuggerDetector
	{
	public:
		bool IsDebuggerPresent() const
		{
			return HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(TGpio), TPin) == TDetectionLevel;
		}
	};
}
