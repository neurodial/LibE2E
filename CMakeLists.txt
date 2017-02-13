cmake_minimum_required(VERSION 2.6)
project(libe2e)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_module/)

find_package(Boost 1.40 COMPONENTS filesystem system REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CppFramework REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CppFramework_INCLUDE_DIRS})

if(CMAKE_COMPILER_IS_GNUCXX)
	set(compiler_flags_debug "-Wall -Wextra -Wunreachable-code -Werror -Wconversion")        ## -Weverything
	set(CMAKE_CXX_FLAGS "-std=c++11")

	if(${WIN32})
		set(CMAKE_CXX_FLAGS "-mno-ms-bitfields -static -static-libstdc++ ${CMAKE_CXX_FLAGS}")
	endif()
endif()


file(GLOB sources_b "${CMAKE_CURRENT_SOURCE_DIR}/E2E/*.cpp")
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/E2E/**/*.cpp")

list(APPEND sources ${sources_b})


if(compiler_flags_debug)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${compiler_flags_debug}")
endif()
if(compiler_flags_release)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${compiler_flags_release}")
endif()
if(compiler_flags)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${compiler_flags}")
endif()




add_library(e2e ${sources})


IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  SET_TARGET_PROPERTIES(e2e PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_executable(libe2e_test main.cpp)
target_link_libraries(libe2e_test e2e ${OpenCV_LIBRARIES})


