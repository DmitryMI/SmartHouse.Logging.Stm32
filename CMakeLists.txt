# CMakeList.txt : CMake project for SmartHouse.Logging.Stm32, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(VCPKG_TARGET_TRIPLET "x64-windows-static-md-v143" CACHE STRING "VCPKG Target Triplet to use")

project ("SmartHouse")

# Include sub-projects.
add_subdirectory ("test")