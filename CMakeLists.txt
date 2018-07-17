cmake_minimum_required(VERSION 2.6)
project(libe2e)

find_package(Boost 1.40 COMPONENTS filesystem system REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OctCppFramework REQUIRED)

set(LibE2E_VERSION 1.0.0)
set(CMAKE_DEBUG_POSTFIX "-d")

include_directories(${CMAKE_SOURCE_DIR}/)
include_directories(${Boost_INCLUDE_DIRS})

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


link_libraries(OctCppFramework::oct_cpp_framework)

add_library(libe2e ${sources})


IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  SET_TARGET_PROPERTIES(libe2e PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

add_executable(libe2e_test main.cpp)
target_link_libraries(libe2e_test libe2e ${OpenCV_LIBRARIES})





set_property(TARGET libe2e PROPERTY VERSION ${LibE2E_VERSION})
set_property(TARGET libe2e PROPERTY SOVERSION 1)
set_property(TARGET libe2e PROPERTY INTERFACE_libe2e_MAJOR_VERSION 1)
set_property(TARGET libe2e APPEND PROPERTY COMPATIBLE_INTERFACE_STRING libe2e_MAJOR_VERSION)

install(TARGETS libe2e EXPORT LibE2ETargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

file(GLOB libe2e_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/E2E/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/E2E/**/*.h")
install(
  FILES
    ${libe2e_HEADERS}
    "${CMAKE_CURRENT_BINARY_DIR}/libe2e_export.h"
  DESTINATION
    include
  COMPONENT
    Devel
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/libe2e/LibE2EConfigVersion.cmake"
  VERSION ${LibE2E_VERSION}
  COMPATIBILITY AnyNewerVersion
)

export(EXPORT LibE2ETargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/libe2e/LibE2ETargets.cmake"
  NAMESPACE LibE2E::
)
configure_file(cmake/LibE2EConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/libe2e/LibE2EConfig.cmake"
  COPY_ONLY
)

target_include_directories(
    libe2e PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/>"
    "$<BUILD_INTERFACE:${generated_headers}>"
)

set(ConfigPackageLocation lib/cmake/libe2e)

install(EXPORT LibE2ETargets
  FILE
    LibE2ETargets.cmake
  NAMESPACE
    LibE2E::
  DESTINATION
    ${ConfigPackageLocation}
)
install(
  FILES
    cmake/LibE2EConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/libe2e/LibE2EConfigVersion.cmake"
  DESTINATION
    ${ConfigPackageLocation}
  COMPONENT
    Devel
)

export(PACKAGE LibE2E)
