#pragma

#pragma once


namespace SmartHouse::Logging::Stm32
{
	template<bool TResult = true>
	class DummyDebuggerDetector
	{
	public:
		constexpr bool IsDebuggerPresent() const
		{
			return TResult;
		}
	};
}