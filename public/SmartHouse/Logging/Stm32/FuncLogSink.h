
namespace SmartHouse::Logging::Stm32
{

	template<auto LogFunc>
	class FuncLogSink
	{
	public:

		void Send(uint8_t c)
		{
			LogFunc(c);
		}
	};
}
