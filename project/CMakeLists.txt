cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(wx_cmake_fetchcontent_template LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxBUILD_TOOLKIT "osx_cocoa" CACHE STRING "Choose toolkit for wxWidgets" FORCE)

set(wxBUILD_SHARED OFF)

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
    sweeper.cpp
)

# Add manifest and resource for Windows
if(WIN32)
    list(APPEND SRCS resources.rc main.exe.manifest)
    add_executable(main WIN32 ${SRCS})
else()
    add_executable(main ${SRCS})
endif()

# Copy the image folder to the build directory
file(COPY img DESTINATION ${CMAKE_BINARY_DIR})

# Link wxWidgets
target_link_libraries(main PRIVATE wx::core wx::base)

# macOS-specific bundle options (optional)
if(APPLE)
    set_target_properties(main PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    )
endif()