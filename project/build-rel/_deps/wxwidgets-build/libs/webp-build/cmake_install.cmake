# Install script for directory: /Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/sharpyuv/libsharpyuv.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/libsharpyuv.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsharpyuv.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsharpyuv.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libsharpyuv.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp/sharpyuv" TYPE FILE FILES
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/sharpyuv/sharpyuv.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/sharpyuv/sharpyuv_csp.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/src/libwebpdecoder.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/src/libwebp.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/src/demux/libwebpdemux.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/src/mux/libwebpmux.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/libwebpdecoder.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebpdecoder.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebpdecoder.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebpdecoder.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/decode.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/libwebp.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebp.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebp.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebp.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/decode.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/encode.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/libwebpdemux.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebpdemux.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebpdemux.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwebpdemux.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/decode.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/demux.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/mux_types.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/liblibwebpmux.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibwebpmux.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibwebpmux.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/liblibwebpmux.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/webp" TYPE FILE FILES
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/mux.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/mux_types.h"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/3rdparty/libwebp/src/webp/types.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake"
         "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/CMakeFiles/Export/3dd5097d708f2adcdf4871ccc089782a/WebPTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/WebP/cmake/WebPTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/CMakeFiles/Export/3dd5097d708f2adcdf4871ccc089782a/WebPTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/CMakeFiles/Export/3dd5097d708f2adcdf4871ccc089782a/WebPTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/WebP/cmake" TYPE FILE FILES
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/WebPConfigVersion.cmake"
    "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/WebPConfig.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webp-build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
