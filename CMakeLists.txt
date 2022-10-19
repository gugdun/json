cmake_minimum_required(VERSION 3.0)
project(json)
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(
  json SHARED
  src/json.cpp
  src/json_parser.cpp
  src/json_token.cpp
  src/json_tokenizer.cpp)

install(TARGETS json DESTINATION /usr/lib)
install(
  FILES include/json.h
        include/json_parser.h
        include/json_token.h
        include/json_tokenizer.h
  DESTINATION include)
