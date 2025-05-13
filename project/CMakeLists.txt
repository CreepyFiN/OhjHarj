cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(wx_cmake_fetchcontent_template LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# macOS-specific wxWidgets option
if(APPLE)
    set(wxBUILD_GUI ON CACHE BOOL "Build GUI" FORCE)
    set(wxBUILD_MONOLITHIC ON CACHE BOOL "Build monolithic wxWidgets" FORCE)
    set(wxBUILD_SHARED OFF CACHE BOOL "Build static wxWidgets" FORCE)    
    set(wxBUILD_TOOLKIT "cocoa" CACHE STRING "Use Cocoa on macOS" FORCE)
endif()

message(STATUS "Fetching wxWidgets...")

FetchContent_Declare(
   wxWidgets
   GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
   GIT_SHALLOW ON
)
FetchContent_MakeAvailable(wxWidgets)

# Source files
set(SRCS 
    main.cpp
)

# Add manifest and resource for Windows
if(WIN32)
    list(APPEND SRCS resources.rc main.exe.manifest)
    add_executable(main WIN32 ${SRCS})
else()
    add_executable(main ${SRCS})
endif()

# Link wxWidgets
target_link_libraries(main PRIVATE wx::core wx::base)

# Platform-specific resource handling
if(APPLE)
    set_target_properties(main PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )

    # Copy img folder into .app bundle
    set(RES_DIR "${CMAKE_BINARY_DIR}/main.app/Contents/Resources")
    file(MAKE_DIRECTORY ${RES_DIR})
    file(COPY img DESTINATION ${RES_DIR})
else()
    # For Windows/Linux: copy img folder next to binary
    file(COPY img DESTINATION ${CMAKE_BINARY_DIR})
endif()
