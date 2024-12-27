#pragma once

#include <cstdint>
#include <string>

namespace SmartHouse::Logging::Stm32
{
	class MemoryLogSink
	{
	public:
		void Send(uint8_t c)
		{
			m_Log += c;
		}

		std::string& GetLog()
		{
			return m_Log;
		}

		void ClearLog()
		{
			m_Log = "";
		}

	private:
		std::string m_Log;
	};
}
