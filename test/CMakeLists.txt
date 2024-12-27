# set minimum cmake version
cmake_minimum_required(VERSION 3.20)

include(FetchContent)

# project name and language
project(SmartHouseSensorsProtocolTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(AppSources 
	"../src/SmartHouse/Logging/Stm32/LogManager.cpp"	
)

set(TestUtilsSources "TestUtils/Logging.cpp" "TestUtils/TestModule.cpp")
set(TestSuitsSources 
	"SmartHouse/Logging/Stm32/LogManagerTest.cpp"
)

enable_testing()

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(spdlog)

# Boost
set(Boost_USE_STATIC_LIBS ON)
set(BOOST_INCLUDE_LIBRARIES program_options test)
set(BOOST_ENABLE_CMAKE ON)
message(STATUS "Downloading and extracting boost library sources. This will take some time...")
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.87.0/boost-1.87.0-cmake.7z
    USES_TERMINAL_DOWNLOAD TRUE 
    GIT_PROGRESS TRUE   
    DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

add_executable(SmarthHouse.Logging.Stm32.Test  ${AppSources} ${TestUtilsSources} ${TestSuitsSources} "SmartHouse/Logging/Stm32/MockTimestampProvider.h")
target_include_directories(SmarthHouse.Logging.Stm32.Test PRIVATE "TestUtils")
target_include_directories(SmarthHouse.Logging.Stm32.Test PRIVATE "../public")
target_link_libraries(SmarthHouse.Logging.Stm32.Test PRIVATE spdlog::spdlog)
target_include_directories(SmarthHouse.Logging.Stm32.Test PRIVATE ${Boost_INCLUDE_DIR} )
target_link_libraries(SmarthHouse.Logging.Stm32.Test PRIVATE Boost::unit_test_framework)
add_test(
  NAME SmarthHouse.Logging.Stm32.Test
  COMMAND $<TARGET_FILE:SmarthHouse.Logging.Stm32.Test>
  )