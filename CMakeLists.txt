cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(CPMExampleKJTLS)

# ---- Create binary ----

add_executable(CPMExampleKJTLS main.cpp)
target_compile_features(CPMExampleKJTLS PRIVATE cxx_std_17)

# ---- Dependencies ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME OpenSSL
  VERSION 1.1.1k
  GITHUB_REPOSITORY janbar/openssl-cmake
  GIT_TAG 1.1.1k-20210430
)

# FindOpenSSL.cmake export uppercase variable
set(OPENSSL_FOUND ${OpenSSL_FOUND})

# janbar/openssl-cmake doesn't provide these targets
add_library(OpenSSL::SSL ALIAS ssl)
add_library(OpenSSL::Crypto ALIAS crypto)

CPMAddPackage(
  NAME CapnProto
  VERSION 0.9.0
  GITHUB_REPOSITORY capnproto/capnproto
  OPTIONS
    "BUILD_TESTING OFF"
    "WITH_OPENSSL ON"
)

target_link_libraries(CPMExampleKJTLS PRIVATE CapnProto::kj-tls)

install(TARGETS CPMExampleKJTLS
  EXPORT CapnProtoTargets
)

export(EXPORT CapnProtoTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/CapnProtoTargets.cmake"
  NAMESPACE CPMExampleKJTLS::
)

install(EXPORT CapnProtoTargets
  FILE CapnProtoTargets.cmake
  NAMESPACE CPMExampleKJTLS::
  DESTINATION lib/cmake/CapnProto
)
