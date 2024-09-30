#pragma once

#include <string_view>

namespace TestUtils
{
	class Logging
	{
	public:
		static void Setup(std::string_view LoggerName);
	};
}