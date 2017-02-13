# - Try to find CppFramework
# Once done this will define
#  CppFramework_FOUND - System has CppFramework
#  CppFramework_INCLUDE_DIRS - The CppFramework include directories
#  CppFramework_LIBRARIES - The libraries needed to use CppFramework
#  CppFramework_DEFINITIONS - Compiler switches required for using CppFramework

find_package(PkgConfig)
# pkg_check_modules(PC_LIBXML QUIET libxml-2.0)
# set(CppFramework_DEFINITIONS ${PC_LIBXML_CFLAGS_OTHER})

find_path(CppFramework_INCLUDE_DIR NAMES cpp_framework PATHS ../
          # HINTS ${PC_LIBXML_INCLUDEDIR} ${PC_LIBXML_INCLUDE_DIRS}
          PATH_SUFFIXES cpp_framework
          )

message(${CppFramework_INCLUDE_DIR})

find_library(CppFramework_LIBRARY NAMES libcpp_framework.a
			PATHS ${CppFramework_INCLUDE_DIR}
			PATH_SUFFIXES build release
             # HINTS ${PC_LIBXML_LIBDIR} ${PC_LIBXML_LIBRARY_DIRS}
             )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CppFramework_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CppFramework DEFAULT_MSG
                                  CppFramework_LIBRARY CppFramework_INCLUDE_DIR)

mark_as_advanced(CppFramework_INCLUDE_DIR CppFramework_LIBRARY )

set(CppFramework_LIBRARIES ${CppFramework_LIBRARY} )
set(CppFramework_INCLUDE_DIRS ${CppFramework_INCLUDE_DIR} )
