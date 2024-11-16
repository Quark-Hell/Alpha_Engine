# Open Asset Import Library (assimp)
# ----------------------------------------------------------------------
# Copyright (c) 2006-2024, assimp team
#
# All rights reserved.
#
# Redistribution and use of this software in source and binary forms,
# with or without modification, are permitted provided that the
# following conditions are met:
#
# * Redistributions of source code must retain the above
#   copyright notice, this list of conditions and the
#   following disclaimer.
#
# * Redistributions in binary form must reproduce the above
#   copyright notice, this list of conditions and the
#   following disclaimer in the documentation and/or other
#   materials provided with the distribution.
#
# * Neither the name of the assimp team, nor the names of its
#   contributors may be used to endorse or promote products
#   derived from this software without specific prior
#   written permission of the assimp team.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#----------------------------------------------------------------------
SET(CMAKE_POLICY_DEFAULT_CMP0012 NEW)
SET(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
SET(CMAKE_POLICY_DEFAULT_CMP0092 NEW)

CMAKE_MINIMUM_REQUIRED( VERSION 3.22 )

# Experimental USD importer: disabled, need to opt-in
# Note: assimp github PR automatic checks will fail the PR due to compiler warnings in
# the external, 3rd party tinyusdz code which isn't technically part of the PR since it's
# auto-cloned during build; so MUST disable the feature or the PR will be rejected
option(ASSIMP_BUILD_USD_IMPORTER "Enable USD file import" off)
option(ASSIMP_BUILD_USD_VERBOSE_LOGS "Enable verbose USD import debug logging" off)

find_program(CCACHE_PATH ccache)
if (CCACHE_PATH)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PATH})
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PATH})
endif()

# Disabled importers: m3d for 5.1 or later
ADD_DEFINITIONS( -DASSIMP_BUILD_NO_M3D_IMPORTER)
ADD_DEFINITIONS( -DASSIMP_BUILD_NO_M3D_EXPORTER)

PROJECT(Assimp VERSION 5.4.3)

# All supported options ###############################################

OPTION ( ASSIMP_WARNINGS_AS_ERRORS
  "Treat all warnings as errors."
  ON
)
OPTION( ASSIMP_DOUBLE_PRECISION
  "Set to ON to enable double precision processing"
  OFF
)


IF (WIN32)
  OPTION( ASSIMP_BUILD_ZLIB
    "Build your zlib"
    ON
  )
ELSE()
  OPTION( ASSIMP_BUILD_ZLIB
    "Build your zlib"
    OFF
  )
ENDIF()

IF (WIN32)
  # Use a subset of Windows.h
  ADD_DEFINITIONS( -DWIN32_LEAN_AND_MEAN )

  IF(MSVC)
    OPTION( ASSIMP_INSTALL_PDB
      "Create MSVC debug symbol files and add to Install target."
      ON )
    IF(NOT (MSVC_VERSION LESS 1900))
      # Multibyte character set has been deprecated since at least MSVC2015 (possibly earlier)
      ADD_DEFINITIONS( -DUNICODE -D_UNICODE )
    ENDIF()

    # Link statically against c/c++ lib to avoid missing redistributable such as
    # "VCRUNTIME140.dll not found. Try reinstalling the app.", but give users
    # a choice to opt for the shared runtime if they want.
    option(USE_STATIC_CRT "Link against the static runtime libraries." OFF)

    # The CMAKE_CXX_FLAGS vars can be overridden by some Visual Studio generators, so we use an alternative
    # global method here:
    if (${USE_STATIC_CRT})
      add_compile_options(
          $<$<CONFIG:>:/MT>
          $<$<CONFIG:Debug>:/MTd>
          $<$<CONFIG:Release>:/MT>
      )
    endif()
  ENDIF()
ENDIF()

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release")
ENDIF()

IF(CMAKE_BUILD_TYPE MATCHES Release)
  ADD_DEFINITIONS(-DENABLE_BITCODE)
ENDIF()

MESSAGE(STATUS "Shared libraries disabled")
SET(LINK_SEARCH_START_STATIC TRUE)
SET(CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_STATIC_LIBRARY_SUFFIX} ${CMAKE_FIND_LIBRARY_SUFFIXES})

# Define here the needed parameters
SET (ASSIMP_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
SET (ASSIMP_VERSION_MINOR ${PROJECT_VERSION_MINOR})
SET (ASSIMP_VERSION_PATCH ${PROJECT_VERSION_PATCH})
SET (ASSIMP_VERSION ${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH})
SET (ASSIMP_SOVERSION 5)

SET(ASSIMP_PACKAGE_VERSION)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)


# Get the current working branch
EXECUTE_PROCESS(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

# Get the latest abbreviated commit hash of the working branch
EXECUTE_PROCESS(
  COMMAND git rev-parse --short=8 HEAD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)


IF(ASSIMP_DOUBLE_PRECISION)
  ADD_DEFINITIONS(-DASSIMP_DOUBLE_PRECISION)
ENDIF()

INCLUDE_DIRECTORIES( BEFORE
  ./
  code/
  include
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/include
)

LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" )
SET(LIBASSIMP_COMPONENT     "libassimp${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH}" )
SET(LIBASSIMP-DEV_COMPONENT "libassimp${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}.${ASSIMP_VERSION_PATCH}-dev" )
SET(CPACK_COMPONENTS_ALL assimp-bin ${LIBASSIMP_COMPONENT} ${LIBASSIMP-DEV_COMPONENT} assimp-dev)
SET(ASSIMP_LIBRARY_SUFFIX "" CACHE STRING "Suffix to append to library names")

IF( UNIX )
  # Use GNUInstallDirs for Unix predefined directories
  INCLUDE(GNUInstallDirs)
  # Ensure that we do not run into issues like http://www.tcm.phy.cam.ac.uk/sw/inodes64.html on 32 bit Linux
  IF(NOT ${OPERATING_SYSTEM} MATCHES "Android")
    IF ( CMAKE_SIZEOF_VOID_P EQUAL 4) # only necessary for 32-bit Linux
      ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 )
    ENDIF()
  ENDIF()
ENDIF()

# Grouped compiler settings ########################################
IF ((CMAKE_C_COMPILER_ID MATCHES "GNU") AND NOT MINGW AND NOT HAIKU)

  SET(CMAKE_POSITION_INDEPENDENT_CODE ON)


  IF(CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 13)
    MESSAGE(STATUS "GCC13 detected disabling \"-Wdangling-reference\" in Cpp files as it appears to be a false positive")
    ADD_COMPILE_OPTIONS("$<$<COMPILE_LANGUAGE:CXX>:-Wno-dangling-reference>")
  ENDIF()
  # hide all not-exported symbols
  IF(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "mips64" )
    SET(CMAKE_CXX_FLAGS "-mxgot -fvisibility=hidden -fno-strict-aliasing -Wall ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
    SET(LIBSTDC++_LIBRARIES -lstdc++)
  ELSE()
    SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall ${CMAKE_CXX_FLAGS}")
    SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
    SET(LIBSTDC++_LIBRARIES -lstdc++)
  ENDIF()
ELSEIF(MSVC)
  # enable multi-core compilation with MSVC
  IF(CMAKE_CXX_COMPILER_ID MATCHES "Clang" ) # clang-cl
    ADD_COMPILE_OPTIONS(/bigobj)
  ELSE() # msvc
    ADD_COMPILE_OPTIONS(/MP /bigobj)
  ENDIF()

  # disable "elements of array '' will be default initialized" warning on MSVC2013
  IF(MSVC12)
    ADD_COMPILE_OPTIONS(/wd4351)
  ENDIF()
  # supress warning for double to float conversion if Double precision is activated
  ADD_COMPILE_OPTIONS(/wd4244)
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D_DEBUG /Zi /Od")
  # Allow user to disable PDBs
  if(ASSIMP_INSTALL_PDB)
    SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:FULL /PDBALTPATH:%_PDB% /OPT:REF /OPT:ICF")
  elseif((GENERATOR_IS_MULTI_CONFIG) OR (CMAKE_BUILD_TYPE MATCHES Release))
    message("-- MSVC PDB generation disabled. Release binary will not be debuggable.")
  endif()
  # Source code is encoded in UTF-8
  ADD_COMPILE_OPTIONS(/source-charset:utf-8)
ELSEIF (CMAKE_CXX_COMPILER_ID MATCHES "Clang" )

  SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

  SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wall -Wno-long-long ${CMAKE_CXX_FLAGS}" )
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ELSEIF( MINGW )
  IF (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
    message(FATAL_ERROR "MinGW is too old to be supported. Please update MinGW and try again.")
  ELSEIF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.3)
    message(WARNING "MinGW is old, if you experience errors, update MinGW.")
  ENDIF()

  SET(CMAKE_CXX_FLAGS "-std=gnu++17 ${CMAKE_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "-fPIC ${CMAKE_C_FLAGS}")

  SET(CMAKE_CXX_FLAGS "-fvisibility=hidden -fno-strict-aliasing -Wno-dangling-reference -Wall -Wno-long-long -Wa,-mbig-obj -O3 ${CMAKE_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "-fno-strict-aliasing ${CMAKE_C_FLAGS}")
ENDIF()

IF (IOS)
  SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -fembed-bitcode -O3")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fembed-bitcode -O3")
ENDIF()

INCLUDE (FindPkgMacros)
INCLUDE (PrecompiledHeader)

# Set Assimp project output directory variables.
# Will respect top-level CMAKE_*_OUTPUT_DIRECTORY variables if any are set.

#Build Directory
get_filename_component(ASSIMP_BUILD "${PROJECT_SOURCE_DIR}/../build/" ABSOLUTE)

SET(ASSIMP_RUNTIME_OUTPUT_DIRECTORY "${ASSIMP_BUILD}/bin")
SET(ASSIMP_LIBRARY_OUTPUT_DIRECTORY "${ASSIMP_BUILD}/bin")
SET(ASSIMP_ARCHIVE_OUTPUT_DIRECTORY "${ASSIMP_BUILD}/lib")


# Macro used to set the output directories of a target to the
# respective Assimp output directories.
MACRO(TARGET_USE_COMMON_OUTPUT_DIRECTORY target)
  set_target_properties(${target} PROPERTIES
      RUNTIME_OUTPUT_DIRECTORY ${ASSIMP_RUNTIME_OUTPUT_DIRECTORY}
      LIBRARY_OUTPUT_DIRECTORY ${ASSIMP_LIBRARY_OUTPUT_DIRECTORY}
      ARCHIVE_OUTPUT_DIRECTORY ${ASSIMP_ARCHIVE_OUTPUT_DIRECTORY}
  )
ENDMACRO()

get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)

IF( UNIX )
  # Use GNUInstallDirs for Unix predefined directories
  INCLUDE(GNUInstallDirs)

  SET( ASSIMP_LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR})
  SET( ASSIMP_INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})
  SET( ASSIMP_BIN_INSTALL_DIR ${CMAKE_INSTALL_BINDIR})
ELSE()
  # Cache these to allow the user to override them on non-Unix platforms
  SET( ASSIMP_LIB_INSTALL_DIR "lib" CACHE STRING
    "Path the built library files are installed to." )
  SET( ASSIMP_INCLUDE_INSTALL_DIR "include" CACHE STRING
    "Path the header files are installed to." )
  SET( ASSIMP_BIN_INSTALL_DIR "bin" CACHE STRING
    "Path the tool executables are installed to." )

  SET(CMAKE_INSTALL_FULL_INCLUDEDIR ${CMAKE_INSTALL_PREFIX}/${ASSIMP_INCLUDE_INSTALL_DIR})
  SET(CMAKE_INSTALL_FULL_LIBDIR ${CMAKE_INSTALL_PREFIX}/${ASSIMP_LIB_INSTALL_DIR})
  SET(CMAKE_INSTALL_FULL_BINDIR ${CMAKE_INSTALL_PREFIX}/${ASSIMP_BIN_INSTALL_DIR})
ENDIF()

set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")

set(CONFIG_INSTALL_DIR "${ASSIMP_LIB_INSTALL_DIR}/cmake/assimp-${ASSIMP_VERSION_MAJOR}.${ASSIMP_VERSION_MINOR}")
set(CMAKE_CONFIG_TEMPLATE_FILE "cmake-modules/assimp-plain-config.cmake.in")
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWERCASE)
set(NAMESPACE "${PROJECT_NAME_LOWERCASE}::")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME_LOWERCASE}Targets")
set(VERSION_CONFIG "${GENERATED_DIR}/${PROJECT_NAME_LOWERCASE}ConfigVersion.cmake")
set(PROJECT_CONFIG "${GENERATED_DIR}/${PROJECT_NAME_LOWERCASE}Config.cmake")

set(INCLUDE_INSTALL_DIR "include")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file("${VERSION_CONFIG}" COMPATIBILITY SameMajorVersion)

configure_package_config_file(
    ${CMAKE_CONFIG_TEMPLATE_FILE}
    "${PROJECT_CONFIG}"
    INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
)

# Search for external dependencies, and build them from source if not found
# Search for zlib

  IF ( NOT ASSIMP_BUILD_ZLIB )
    FIND_PACKAGE(ZLIB)
  ENDIF()

  IF ( NOT ZLIB_FOUND AND NOT ASSIMP_BUILD_ZLIB )
    message( FATAL_ERROR
      "Build configured with -DASSIMP_BUILD_ZLIB=OFF but unable to find zlib"
    )
  ELSEIF( NOT ZLIB_FOUND )
    MESSAGE(STATUS "compiling zlib from sources")
    INCLUDE(CheckIncludeFile)
    INCLUDE(CheckTypeSize)
    INCLUDE(CheckFunctionExists)

    # Explicitly turn off ASM686 and AMD64 cmake options.
    # The AMD64 option causes a build failure on MSVC and the ASM builds seem to have problems:
    #		https://github.com/madler/zlib/issues/41#issuecomment-125848075
    # Also prevents these options from "polluting" the cmake options if assimp is being
    # included as a submodule.
    set( ASM686 FALSE CACHE INTERNAL "Override ZLIB flag to turn off assembly" FORCE )
    set( AMD64 FALSE CACHE INTERNAL "Override ZLIB flag to turn off assembly" FORCE )

    # compile from sources
    ADD_SUBDIRECTORY(contrib/zlib)
    SET(ZLIB_FOUND 1)
    SET(ZLIB_LIBRARIES zlibstatic)
    SET(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib/zlib ${CMAKE_CURRENT_BINARY_DIR}/contrib/zlib)
    # need to ensure we don't link with system zlib or minizip as well.
    SET(ASSIMP_BUILD_MINIZIP 1)
  ELSE()
    ADD_DEFINITIONS(-DASSIMP_BUILD_NO_OWN_ZLIB)
    SET(ZLIB_LIBRARIES_LINKED -lz)
  ENDIF()
  INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIR})

IF( NOT IOS )
  IF( NOT ASSIMP_BUILD_MINIZIP )
    use_pkgconfig(UNZIP minizip)
  ENDIF()
ELSE ()
  IF( NOT ASSIMP_BUILD_MINIZIP )
    use_pkgconfig(UNZIP minizip)
  ENDIF ()
ENDIF ()

SET ( ASSIMP_BUILD_ARCHITECTURE "" CACHE STRING
  "describe the current architecture."
)
IF( ASSIMP_BUILD_ARCHITECTURE STREQUAL "")
ELSE()
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_ARCHITECTURE="${ASSIMP_BUILD_ARCHITECTURE}"' )
ENDIF()

# ${CMAKE_GENERATOR}
SET ( ASSIMP_BUILD_COMPILER "" CACHE STRING
  "describe the current compiler."
)
IF( ASSIMP_BUILD_COMPILER STREQUAL "")
ELSE()
  ADD_DEFINITIONS ( -D'ASSIMP_BUILD_COMPILER="${ASSIMP_BUILD_COMPILER}"' )
ENDIF()

MARK_AS_ADVANCED ( ASSIMP_BUILD_ARCHITECTURE ASSIMP_BUILD_COMPILER )

if(ASSIMP_BUILD_DRACO_STATIC)
  set(ASSIMP_BUILD_DRACO ON)
endif()

# Main assimp code
ADD_SUBDIRECTORY( code/ )

# Generate a pkg-config .pc, revision.h, and config.h for the Assimp library.
CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/assimp.pc.in" "${PROJECT_BINARY_DIR}/assimp.pc" @ONLY )

CONFIGURE_FILE(
  ${CMAKE_CURRENT_LIST_DIR}/include/assimp/revision.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/assimp/revision.h
)

CONFIGURE_FILE(
  ${CMAKE_CURRENT_LIST_DIR}/include/assimp/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/assimp/config.h
)

if(WIN32)
  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(BIN_DIR "${PROJECT_SOURCE_DIR}/bin64/")
    SET(LIB_DIR "${PROJECT_SOURCE_DIR}/lib64/")
  else()
    SET(BIN_DIR "${PROJECT_SOURCE_DIR}/bin32/")
    SET(LIB_DIR "${PROJECT_SOURCE_DIR}/lib32/")
  ENDIF()

  IF(MSVC_TOOLSET_VERSION)
    SET(MSVC_PREFIX "vc${MSVC_TOOLSET_VERSION}")
    SET(ASSIMP_MSVC_VERSION ${MSVC_PREFIX})
  ELSE()
    IF(MSVC12)
      SET(ASSIMP_MSVC_VERSION "vc120")
    ELSEIF(MSVC14)
      SET(ASSIMP_MSVC_VERSION "vc140")
    ELSEIF(MSVC15)
      SET(ASSIMP_MSVC_VERSION "vc141")
    ELSEIF(MSV142)
      SET(ASSIMP_MSVC_VERSION "vc142")
    ELSEIF(MSVC143)
      SET(ASSIMP_MSVC_VERSION "vc143")
    ENDIF()
  ENDIF()

  IF(MSVC12 OR MSVC14 OR MSVC15 )
    ADD_CUSTOM_TARGET(UpdateAssimpLibsDebugSymbolsAndDLLs COMMENT "Copying Assimp Libraries ..." VERBATIM)
    IF(CMAKE_GENERATOR MATCHES "^Visual Studio")
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Release/assimp-${ASSIMP_MSVC_VERSION}-mt.dll	${BIN_DIR}assimp-${ASSIMP_MSVC_VERSION}-mt.dll VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Release/assimp-${ASSIMP_MSVC_VERSION}-mt.exp	${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mt.exp VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Release/assimp-${ASSIMP_MSVC_VERSION}-mt.lib	${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mt.lib VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Debug/assimp-${ASSIMP_MSVC_VERSION}-mtd.dll		${BIN_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.dll  VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Debug/assimp-${ASSIMP_MSVC_VERSION}-mtd.exp		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.exp VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Debug/assimp-${ASSIMP_MSVC_VERSION}-mtd.ilk		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.ilk VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Debug/assimp-${ASSIMP_MSVC_VERSION}-mtd.lib		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.lib VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/Debug/assimp-${ASSIMP_MSVC_VERSION}-mtd.pdb		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.pdb VERBATIM)
    ELSE()
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mt.dll	${BIN_DIR}assimp-${ASSIMP_MSVC_VERSION}-mt.dll VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mt.exp	${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mt.exp VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mt.lib	${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mt.lib VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mtd.dll		${BIN_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.dll  VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mtd.exp		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.exp VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mtd.ilk		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.ilk VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mtd.lib		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.lib VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mtd.pdb		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.pdb VERBATIM)
      ADD_CUSTOM_COMMAND(TARGET UpdateAssimpLibsDebugSymbolsAndDLLs COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/code/assimp-${ASSIMP_MSVC_VERSION}-mtd.pdb		${LIB_DIR}assimp-${ASSIMP_MSVC_VERSION}-mtd.pdb VERBATIM)
    ENDIF()
  ENDIF()
ENDIF ()
