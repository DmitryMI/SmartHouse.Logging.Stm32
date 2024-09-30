#pragma once

#include <string>

namespace SmartHouse::Logging::Stm32
{
	class CounterTimestampProvider
	{
	public:
		std::string GetTimestampString()
		{
			std::string temp = std::to_string(m_Counter);
			m_Counter++;
			return temp;
		}
	private:
		uint64_t m_Counter = 0;
	};
}