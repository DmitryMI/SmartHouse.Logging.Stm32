set(CMAKE_CXX_STANDARD 20)

set(SmartHouse.Logging.Stm32.Sources.Relative 
	"SmartHouse/Logging/Stm32/LogManager.cpp"
)

set(SmartHouse.Logging.Stm32.Headers.Relative "../public")

set(SmartHouse.Logging.Stm32.Headers PARENT_SCOPE)
set(SmartHouse.Logging.Stm32.Sources PARENT_SCOPE)

foreach(REL_PATH IN LISTS SmartHouse.Logging.Stm32.Headers.Relative)
    get_filename_component(ABS_PATH "${REL_PATH}" ABSOLUTE)
    list(APPEND SmartHouse.Logging.Stm32.Headers "${ABS_PATH}")
endforeach()

foreach(REL_PATH IN LISTS SmartHouse.Logging.Stm32.Sources.Relative)
    get_filename_component(ABS_PATH "${REL_PATH}" ABSOLUTE)
    list(APPEND SmartHouse.Logging.Stm32.Sources "${ABS_PATH}")
endforeach()

message(STATUS "SmartHouse.Logging.Stm32.Sources: ")
foreach(ABS_PATH IN LISTS SmartHouse.Logging.Stm32.Sources)
    message(STATUS "${ABS_PATH}")
endforeach()

message(STATUS "SmartHouse.Logging.Stm32.Headers: ")
foreach(ABS_PATH IN LISTS SmartHouse.Logging.Stm32.Headers)
    message(STATUS "${ABS_PATH}")
endforeach()


# add_library(SmartHouse.Logging.Stm32 ${AppSources})
# target_include_directories(SmartHouse.Logging.Stm32 PUBLIC ../public)