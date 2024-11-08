#pragma once

#include <stdarg.h>
#include <stdint.h>

namespace SmartHouse::Logging::Stm32
{
	class SprintfFormatter
	{
	public:
		int AsVsnprintf(char* buffer, size_t bufferSize, const char* format, va_list args) const
		{
#ifdef _MSC_VER
			return vsprintf_s(buffer, bufferSize, format, args);
#elif defined(__GNUC__)
			return vsnprintf(buffer, bufferSize, format, args);
#else
#error "This compiler is not supported!"
#endif
		}

		int AsSnprintf(char* buffer, size_t bufferSize, const char* format, ...) const
		{
			va_list args;
			va_start(args, format);
			int result = AsVsnprintf(buffer, bufferSize, format, args);
			va_end(args);
			return result;
		}
	};
}