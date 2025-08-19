set(CMAKE_CXX_STANDARD 20)

set(SmartHouse.Logging.Stm32.Sources 
	"SmartHouse/Logging/Stm32/LogManager.cpp"
)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(SmartHouse.Logging.Stm32 ${SmartHouse.Logging.Stm32.Sources})
target_include_directories(SmartHouse.Logging.Stm32 PUBLIC ../public)