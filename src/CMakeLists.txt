set(CMAKE_CXX_STANDARD 20)

set(SmartHouse.Logging.Stm32.Sources.Relative 
	"SmartHouse/Logging/Stm32/LogManager.cpp"
)

set(SmartHouse.Logging.Stm32.Headers.Relative "../public")

set(SmartHouse.Logging.Stm32.Headers.Absolute)
set(SmartHouse.Logging.Stm32.Sources.Absolute)

foreach(REL_PATH IN LISTS SmartHouse.Logging.Stm32.Headers.Relative)
    get_filename_component(ABS_PATH "${REL_PATH}" ABSOLUTE)
    list(APPEND SmartHouse.Logging.Stm32.Headers.Absolute "${ABS_PATH}")
endforeach()

foreach(REL_PATH IN LISTS SmartHouse.Logging.Stm32.Sources.Relative)
    get_filename_component(ABS_PATH "${REL_PATH}" ABSOLUTE)
    list(APPEND SmartHouse.Logging.Stm32.Sources.Absolute "${ABS_PATH}")
endforeach()

message(STATUS "SmartHouse.Logging.Stm32.Sources: ")
foreach(ABS_PATH IN LISTS SmartHouse.Logging.Stm32.Sources.Absolute)
    message(STATUS "\t${ABS_PATH}")
endforeach()

message(STATUS "SmartHouse.Logging.Stm32.Headers: ")
foreach(ABS_PATH IN LISTS SmartHouse.Logging.Stm32.Headers.Absolute)
    message(STATUS "\t${ABS_PATH}")
endforeach()

set(SmartHouse.Logging.Stm32.Headers ${SmartHouse.Logging.Stm32.Headers.Absolute} PARENT_SCOPE)
set(SmartHouse.Logging.Stm32.Sources ${SmartHouse.Logging.Stm32.Sources.Absolute} PARENT_SCOPE)


# add_library(SmartHouse.Logging.Stm32 ${AppSources})
# target_include_directories(SmartHouse.Logging.Stm32 PUBLIC ../public)