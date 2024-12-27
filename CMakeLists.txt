# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

option(SMARTHOUSE_BUILD_TESTS "Build unit tests" OFF)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(VCPKG_TARGET_TRIPLET "x64-windows-static-md-v143" CACHE STRING "VCPKG Target Triplet to use")

project ("SmartHouse")

# Include sub-projects.
add_subdirectory("src")

if(SMARTHOUSE_BUILD_TESTS)
	add_subdirectory("test")
endif()