#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <string>

namespace SmartHouse::Logging::Stm32
{
	enum class FormatFlags : uint8_t
	{
		LeftJustify = (1 << 0),
		ForceSign = (1 << 1),
		ZeroPadding = (1 << 2)
	};

	enum class FormatParameterState
	{
		NotDefined,
		Static,
		Dynamic
	};

	enum class FormatLength
	{
		None,
		Long,
		LongLong
	};

	struct FormatSpecifier
	{
		FormatFlags m_Flags = static_cast<FormatFlags>(0);
		FormatParameterState m_WidthState = FormatParameterState::NotDefined;
		uint32_t m_Width = 0;
		FormatParameterState m_PrecisionState = FormatParameterState::NotDefined;
		uint32_t m_Precision = 0;
		FormatLength m_Length = FormatLength::None;

		bool HasFlag(FormatFlags flag)
		{
			return static_cast<uint8_t>(m_Flags) & static_cast<uint8_t>(flag);
		}

		void SetFlag(FormatFlags flag)
		{
			m_Flags = static_cast<FormatFlags>(static_cast<uint8_t>(m_Flags) | static_cast<uint8_t>(flag));
		}
	};

	class SmallFormatter
	{
	public:

		
		int AsVsnprintf(char* buffer, size_t bufferSize, const char* format, va_list args) const
		{
			size_t bufferPos = 0;
			int argIndex = 0;
			std::string placeholder = "";
			for (int i = 0; format[i] != '\0' && bufferPos < bufferSize; i++)
			{
				if (format[i] != '%' && placeholder.size() == 0)
				{
					buffer[bufferPos] = format[i];
					bufferPos++;
					continue;
				}

				placeholder.push_back(format[i]);
				if (placeholder.size() == 2 && placeholder[1] == '%')
				{
					buffer[bufferPos] = '%';
					bufferPos++;
					placeholder = "";
					continue;
				}

				char typeSpecifier = placeholder[placeholder.size() - 1];
				bool formatSpecifierComplete = false;
				std::string valueString = "";
				FormatSpecifier formatSpecifier;

				if (typeSpecifier == 's')
				{
					formatSpecifier = ParseFormatSpecifier(placeholder);
					
					if (formatSpecifier.m_WidthState == FormatParameterState::Dynamic)
					{
						int width = va_arg(args, int);
					}
					char* value = va_arg(args, char*);
					int valueLen = strlen(value);
					if (valueLen > bufferSize - bufferPos)
					{
						valueLen = bufferSize - bufferPos;
					}
					valueString = std::string(value, valueLen);
					formatSpecifierComplete = true;
				}
				else if (typeSpecifier == 'd' || typeSpecifier == 'i' || typeSpecifier == 'x')
				{
					formatSpecifier = ParseFormatSpecifier(placeholder);
					int valueSign = 0;
					switch (formatSpecifier.m_Length)
					{
					case FormatLength::None:
					{
						auto value = va_arg(args, int);
						valueSign = GetSign(value);
						if (typeSpecifier != 'x')
						{
							valueString = std::to_string(value);
						}
						else
						{
							valueString = ToHexString(value);
						}
						break;
					}
					case FormatLength::Long:
					{
						auto value = va_arg(args, long);
						valueSign = GetSign(value);
						if (typeSpecifier != 'x')
						{
							valueString = std::to_string(value);
						}
						else
						{
							valueString = ToHexString(value);
						}
						break;
					}
					case FormatLength::LongLong:
					{
						auto value = va_arg(args, long long);
						valueSign = GetSign(value);
						if (typeSpecifier != 'x')
						{
							valueString = std::to_string(value);
						}
						else
						{
							valueString = ToHexString(value);
						}
						break;
					}
					default:
					{
						auto value = va_arg(args, int);
						valueSign = GetSign(value);
						if (typeSpecifier != 'x')
						{
							valueString = std::to_string(value);
						}
						else
						{
							valueString = ToHexString(value);
						}
						break;
					}
					}
					if (formatSpecifier.HasFlag(FormatFlags::ForceSign) && valueSign != -1)
					{
						valueString.insert(valueString.begin(), '+');
					}

					formatSpecifierComplete = true;
				}
				else if (typeSpecifier == 'f')
				{
					double value = va_arg(args, double);
					valueString = ToString(value, 2);
					formatSpecifierComplete = true;
				}

				if (!formatSpecifierComplete)
				{
					continue;
				}

				bufferPos += CopyString(valueString, buffer + bufferPos, bufferSize - bufferPos);
				placeholder = "";
			}

			if (bufferPos == bufferSize)
			{
				bufferPos--;
			}
			buffer[bufferPos] = '\0';

			return bufferPos + 1;
		}

		int AsSnprintf(char* buffer, size_t bufferSize, const char* format, ...) const
		{
			va_list args;
			va_start(args, format);
			int result = AsVsnprintf(buffer, bufferSize, format, args);
			va_end(args);
			return result;
		}

	private:
		template <typename I>
		static std::string ToHexString(I w, size_t hex_len = sizeof(I) << 1) {
			static const char* digits = "0123456789ABCDEF";
			std::string rc(hex_len, '0');
			for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
			{
				rc[i] = digits[(w >> j) & 0x0f];
			}
			return rc;
		}

		static size_t CopyString(const std::string& from, char* to, size_t maxBytes)
		{
			if (from.size() < maxBytes)
			{
				maxBytes = from.size();
			}

			memcpy(to, from.c_str(), maxBytes);

			return maxBytes;
		}

		static size_t CopyString(const char* from, char* to, size_t maxBytes)
		{
			size_t i = 0;
			for (i = 0; i < maxBytes && from[i] != '\0'; i++)
			{
				to[i] = from[i];
			}

			return i;
		}

		template<typename T>
		static constexpr int GetSign(T value)
		{
			if (value == 0)
			{
				return 0;
			}
			if (value > 0)
			{
				return 1;
			}
			return 0;
		}

		static std::string ToString(float Value, int DigitsAfterPoint)
		{
			uint32_t Integer = static_cast<uint32_t>(Value);
			float Fraction = Value - Integer;

			std::string Result = std::to_string(Integer);

			Result += ".";

			for (int I = 0; I < DigitsAfterPoint; I++)
			{
				Fraction *= 10;
				uint32_t FractionInt = static_cast<uint32_t>(Fraction);
				uint32_t Digit = FractionInt % 10;
				char Symbol = Digit + 0x30;
				Result += Symbol;
			}

			return Result;
		}

		// %[flags][width][.precision][length]specifier
		static FormatSpecifier ParseFormatSpecifier(const std::string& formatSpecifierString)
		{
			FormatSpecifier specifier;
			constexpr int stateFlags = 0;
			constexpr int stateWidth = 1;
			constexpr int statePrecision = 2;
			constexpr int stateLength = 3;
			int state = stateFlags;
			std::string token = "";

			for (size_t i = 1; i < formatSpecifierString.size(); i++)
			{
				if (state == stateFlags)
				{
					if (formatSpecifierString[i] == '+')
					{
						specifier.SetFlag(FormatFlags::ForceSign);
					}
					else if (formatSpecifierString[i] == '-')
					{
						specifier.SetFlag(FormatFlags::LeftJustify);
					}
					else if (formatSpecifierString[i] == '0')
					{
						specifier.SetFlag(FormatFlags::ZeroPadding);
					}
					else
					{
						state = stateWidth;
						i--;
					}
				}
				else if (state == stateWidth)
				{
					if (formatSpecifierString[i] == '*')
					{
						state = statePrecision;
						specifier.m_WidthState = FormatParameterState::Dynamic;
					}
					else if (std::isdigit(formatSpecifierString[i]))
					{
						token.push_back(formatSpecifierString[i]);
					}
					else
					{
						if (token.size() > 0)
						{
							specifier.m_WidthState = FormatParameterState::Static;
							specifier.m_Width = std::atoi(token.c_str());
							token = "";
						}
						state = statePrecision;
						i--;
					}
				}
				else if (state == statePrecision)
				{
					if (formatSpecifierString[i] == '.')
					{
						continue;
					}
					else if (formatSpecifierString[i] == '*')
					{
						state = stateLength;
						specifier.m_PrecisionState = FormatParameterState::Dynamic;
					}
					else if (std::isdigit(formatSpecifierString[i]))
					{
						token.push_back(formatSpecifierString[i]);
					}
					else
					{
						if (token.size() > 0)
						{
							specifier.m_PrecisionState = FormatParameterState::Static;
							specifier.m_Precision = std::atoi(token.c_str());
							token = "";
						}
						state = stateLength;
						i--;
					}
				}
				else if (state == stateLength)
				{
					if (formatSpecifierString[i] == 'l' && formatSpecifierString[i+ 1 ] != 'l')
					{
						specifier.m_Length = FormatLength::Long;
					}
					else if (formatSpecifierString[i] == 'l' && formatSpecifierString[i + 1] == 'l')
					{
						specifier.m_Length = FormatLength::LongLong;
					}
					else
					{
						specifier.m_Length = FormatLength::None;
					}
					break;
				}
			}
			return specifier;
		}
	};
}