# set minimum cmake version
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TestSuitsSources 
	"SmartHouse/Logging/Stm32/LogManagerTest.cpp"
)

enable_testing()

find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_executable(SmarthHouse.Logging.Stm32.Test ${TestSuitsSources})
target_link_libraries(SmarthHouse.Logging.Stm32.Test PRIVATE SmartHouse.Logging.Stm32)
target_link_libraries(SmarthHouse.Logging.Stm32.Test PRIVATE spdlog::spdlog)
target_link_libraries(SmarthHouse.Logging.Stm32.Test PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(SmarthHouse.Logging.Stm32.Test)