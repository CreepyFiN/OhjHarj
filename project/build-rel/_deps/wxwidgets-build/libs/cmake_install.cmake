# Install script for directory: /Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-src/build/cmake/lib

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/lib/libwxregexu-3.3.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxregexu-3.3.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxregexu-3.3.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxregexu-3.3.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/lib/libwxjpeg-3.3.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxjpeg-3.3.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxjpeg-3.3.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxjpeg-3.3.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/lib/libwxpng-3.3.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxpng-3.3.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxpng-3.3.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxpng-3.3.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/lib/libwxtiff-3.3.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxtiff-3.3.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxtiff-3.3.a")
    execute_process(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libwxtiff-3.3.a")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/base/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/net/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/core/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/adv/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/aui/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/html/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/propgrid/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/ribbon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/richtext/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/webview/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/stc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/xrc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/media/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/gl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/qa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/xml/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/veetivelin/Documents/Koulu/Ohjelmointi/Ohjelmoinnin Harjoitustyö/OhjHarj/project/build-rel/_deps/wxwidgets-build/libs/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
