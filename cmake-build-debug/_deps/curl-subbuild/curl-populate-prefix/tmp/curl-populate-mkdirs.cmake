# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-src"
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-build"
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix"
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/tmp"
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp"
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src"
  "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/duno/CLionProjects/HTTP/cmake-build-debug/_deps/curl-subbuild/curl-populate-prefix/src/curl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
