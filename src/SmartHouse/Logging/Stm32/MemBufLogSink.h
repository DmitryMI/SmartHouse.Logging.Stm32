#pragma once

#include <vector>
#include <string>

namespace SmartHouse::Logging::Stm32
{
	class MemBufLogSink
	{
	public:
		void Send(const char* buffer, size_t size)
		{
			std::string message = std::string(buffer, size);
			m_Messages.push_back(message);
		}

		std::vector<std::string>& GetMessageBuffer()
		{
			return m_Messages;
		}

	private:
		std::vector<std::string> m_Messages;
	};
}