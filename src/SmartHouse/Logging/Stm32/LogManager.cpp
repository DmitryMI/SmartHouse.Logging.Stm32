#include "SmartHouse/Logging/Stm32/LogManager.h"

#ifdef __GNUC__
#include <unistd.h>
#endif

extern "C"
{
#ifdef __GNUC__
	int __io_putchar(int ch)
	{
		GLogManager.PutCharCallback(ch);
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
				GLogManager.PutCharCallback(ch);
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
