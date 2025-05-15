# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-src")
  file(MAKE_DIRECTORY "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-src")
endif()
file(MAKE_DIRECTORY
  "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-build"
  "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix"
  "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix/tmp"
  "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix/src/wxwidgets-populate-stamp"
  "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix/src"
  "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix/src/wxwidgets-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix/src/wxwidgets-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Github/OhjHarj/project/uild/_deps/wxwidgets-subbuild/wxwidgets-populate-prefix/src/wxwidgets-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
