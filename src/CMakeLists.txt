set(CMAKE_CXX_STANDARD 20)

set(AppSources 
	"SmartHouse/Logging/Stm32/LogManager.cpp"
	
)
add_library(SmartHouse.Logging.Stm32 ${AppSources})
target_include_directories(SmartHouse.Logging.Stm32 PUBLIC ../public)