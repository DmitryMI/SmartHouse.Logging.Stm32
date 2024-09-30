#pragma once

#ifdef _MSC_VER
	using HAL_GPIO_TypeDef = void*;
	#define HAL_GPIO_ReadPin(port, pin) (0);
#endif


namespace SmartHouse::Logging::Stm32
{
	template<HAL_GPIO_TypeDef TGpio, uint16_t TPin, int TDetectionLevel = 0>
	class GpioDebuggerDetector
	{
	public:
		bool IsDebuggerPresent() const
		{
			return HAL_GPIO_ReadPin(TGpio, TPin) == TDetectionLevel;
		}
	};
}