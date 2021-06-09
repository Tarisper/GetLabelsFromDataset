cmake_minimum_required (VERSION 3.18...3.20 FATAL_ERROR)

# ---[ Solution.
project (GetLabels
  VERSION 0.1.0.0
  DESCRIPTION "Get all labels from files."
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

# ---[ Modules.
include (GNUInstallDirs)

# ---[ Options.
option (BUILD_SHARED_LIBS "Build shared libraries." ON)
option (BUILD_PACKAGING "Build distribution packages using CPack." ON)

# ---[ General dependencies.
list (APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
list (APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

# ---[ Conan.
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message (STATUS "Downloading conan.cmake from 'https://github.com/conan-io/cmake-conan'.")
  file (DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake"
    SHOW_PROGRESS
    INACTIVITY_TIMEOUT 15
    TIMEOUT 30
#    EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
    TLS_VERIFY ON
    STATUS CONAN_CMAKE_DOWNLOAD_RESULT
  )
  if (NOT CONAN_CMAKE_DOWNLOAD_RESULT EQUAL 0)
    message (WARNING "Failed conan.cmake downloading. Error: ${CONAN_CMAKE_DOWNLOAD_RESULT}. Local copy is used.")
    file (COPY "${CMAKE_SOURCE_DIR}/cmake/conan.cmake" DESTINATION "${CMAKE_BINARY_DIR}")
  endif ()
endif ()
include ("${CMAKE_BINARY_DIR}/conan.cmake")

conan_check (VERSION 1.37 REQUIRED)
set (CONAN_IMPORTS
  "bin, *.dll -> ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
  "lib, *.dylib* -> ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
  "lib, *.so* -> ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
)
conan_cmake_configure (
  REQUIRES
    "nlohmann_json/3.9.1"
  OPTIONS

  IMPORTS ${CONAN_IMPORTS}
)
conan_cmake_autodetect (CONAN_SETTINGS)
conan_cmake_install (
  PATH_OR_REFERENCE "."
  GENERATOR cmake
  BUILD missing
  REMOTE conan-center
  SETTINGS ${CONAN_SETTINGS}
)
if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
  include ("${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake")
else ()
  include ("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
endif ()
conan_basic_setup (TARGETS KEEP_RPATHS NO_OUTPUT_DIRS)

# ---[ Projects.
add_subdirectory ("projects")

# ---[ Pack rules.
if (BUILD_PACKAGING)
  set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
  set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
  set (CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
  set (CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
  set (CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
  set (CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
  include (CPack)
endif ()
