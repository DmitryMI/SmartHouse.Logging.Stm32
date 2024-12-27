#include "SmartHouse/Logging/Stm32/LogManager.h"

#ifdef __GNUC__
#include <unistd.h>
#endif

namespace SmartHouse::Logging::Stm32
{
	void LogManagerPutCharCallbackPlaceholder(uint8_t c)
	{

	}

	std::function<void(uint8_t)> LogManagerPutCharCallback = LogManagerPutCharCallbackPlaceholder;
}

extern "C"
{
#ifdef __GNUC__
	int __io_putchar(int ch)
	{
		LogManagerPutCharCallback(ch);
		return ch;
	}

	int _write(int file, char* ptr, int len)
	{
		switch (file)
		{
		case STDOUT_FILENO:
		case STDERR_FILENO:
			for (int i = 0; i < len; i++)
			{
				LogManagerPutCharCallback(ch);
			}
			break;
		case STDIN_FILENO:
			break;
		default:
			return -1;
			break;
		}
		return len;
	}
#endif

}
