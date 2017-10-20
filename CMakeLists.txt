cmake_minimum_required(VERSION 3.1)
project(binance-trading)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/catch/single_include)
set(CATCH_INCLUDE_DIR ${CATCH_INCLUDE_DIR} PARENT_SCOPE)
set(RANGEV3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/range-v3/include)
set(RANGEV3_INCLUDE_DIR ${RANGEV3_INCLUDE_DIR} PARENT_SCOPE)
set(FMT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/fmt)
set(FMT_INCLUDE_DIR ${FMT_INCLUDE_DIR} PARENT_SCOPE)
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/json/src)
set(JSON_INCLUDE_DIR ${JSON_INCLUDE_DIRS} PARENT_SCOPE)
set(Boost_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/boost)
set(Boost_INCLUDE_DIR ${Boost_INCLUDE_DIR} PARENT_SCOPE)
set(Boost_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/library_boost/lib)
set(Boost_LIBRARY_DIR ${Boost_LIBRARY_DIR} PARENT_SCOPE)
set(CRYPTO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/cryptlite/include)
set(CRYPTO_INCLUDE_DIR ${CRYPTO_INCLUDE_DIRS} PARENT_SCOPE)
set(OPENSSL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/library_openssl/include)
set(OPENSSL_INCLUDE_DIR ${OPENSSL_INCLUDE_DIR} PARENT_SCOPE)
set(OPENSSL_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/library_openssl/lib)
set(OPENSSL_LIBRARIES ${OPENSSL_LIBRARIES} PARENT_SCOPE)
set(BEAST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/beast/include)
set(BEAST_INCLUDE_DIR ${BEAST_INCLUDE_DIR} PARENT_SCOPE)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(Boost_USE_STATIC_LIBS ON)
find_package(
  Boost
  COMPONENTS
  system
  random
  thread
  REQUIRED)
link_directories(
  ${Boost_LIBRARY_DIR}
  ${OPENSSL_LIBRARIES})

if(WIN32)
    option(CMAKE_USE_OPENSSL "Use OpenSSL code. Experimental" OFF)
endif()

set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")
find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()
add_subdirectory(libs/cpr)

include_directories(
  ${CATCH_INCLUDE_DIR}
  ${RANGEV3_INCLUDE_DIR}
  ${FMT_INCLUDE_DIR}
  ${CPR_INCLUDE_DIR}
  ${JSON_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
  ${CRYPTO_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
  ${BEAST_INCLUDE_DIR}
  )

cpr_option(BUILD_BINANCE_EXEC "Set to ON to build binance exec." ON)
cpr_option(BUILD_BINANCE_TESTS "Set to ON to build binance tests." ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

if(BUILD_BINANCE_EXEC)
  add_executable(binance_exec main.cc)
  target_link_libraries(
    binance_exec
    ${OPENSSL_LIBRARIES}/libssl.a
    ${OPENSSL_LIBRARIES}/libcrypto.a
    ${Boost_LIBRARIES}
    ${CPR_LIBRARIES}
    "-ldl"
    )
endif()

if(BUILD_BINANCE_TESTS)
  add_executable(binance_tests test/tests.cc)
  target_link_libraries(
    binance_tests
    ${OPENSSL_LIBRARIES}/libssl.a
    ${OPENSSL_LIBRARIES}/libcrypto.a
    ${Boost_LIBRARIES}
    ${CPR_LIBRARIES}
    "-ldl"
    )

  enable_testing()
  add_test(NAME Tests COMMAND binance_tests)
endif()

if(BUILD_BINANCE_EXEC AND BUILD_BINANCE_TESTS)
  add_dependencies(binance_exec binance_tests)
endif()
