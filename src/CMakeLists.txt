set(CMAKE_CXX_STANDARD 20)

set(SmartHouse.Logging.Stm32.Sources 
	"SmartHouse/Logging/Stm32/LogManager.cpp"
	PARENT_SCOPE
)

set(SmartHouse.Logging.Stm32.Headers "../public" PARENT_SCOPE)

# add_library(SmartHouse.Logging.Stm32 ${AppSources})
# target_include_directories(SmartHouse.Logging.Stm32 PUBLIC ../public)