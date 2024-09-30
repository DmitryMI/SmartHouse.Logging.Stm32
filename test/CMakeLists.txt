# set minimum cmake version
cmake_minimum_required(VERSION 3.20)

set(spdlog_DIR "D:/Software/vcpkg/installed/x64-windows-static-md-v143/share/spdlog" CACHE STRING "Path to spdlog")
set(fmt_DIR "D:/Software/vcpkg/installed/x64-windows-static-md-v143/share/fmt" CACHE STRING "Path to fmt")
set(Boost_ROOT "C:/Software/boost_1_85_0" CACHE STRING "Path to Boost")

# project name and language
project(SmartHouseSensorsProtocolTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AppSources 
		
)

set(TestUtilsSources "TestUtils/Logging.cpp" "TestUtils/TestModule.cpp")
set(TestSuitsSources 
	"SmartHouse/Logging/Stm32/LogManagerTest.cpp"
)

enable_testing()

# spdlog
find_package(spdlog CONFIG REQUIRED)

# Boost
set(Boost_USE_STATIC_LIBS ON)
find_package( Boost 1.80 REQUIRED COMPONENTS program_options unit_test_framework)

add_executable(SmarthHouseLoggingStm32Test  ${AppSources} ${TestUtilsSources} ${TestSuitsSources})
target_include_directories(SmarthHouseLoggingStm32Test PRIVATE "TestUtils")
target_include_directories(SmarthHouseLoggingStm32Test PRIVATE "../src/SmartHouse/Logging/Stm32/")
target_link_libraries(SmarthHouseLoggingStm32Test PRIVATE spdlog::spdlog)
target_include_directories(SmarthHouseLoggingStm32Test PRIVATE ${Boost_INCLUDE_DIR} )
target_link_libraries(SmarthHouseLoggingStm32Test PRIVATE ${Boost_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(
  NAME SmarthHouseLoggingStm32Test
  COMMAND $<TARGET_FILE:SmarthHouseLoggingStm32Test>
  )