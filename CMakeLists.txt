cmake_minimum_required(VERSION 2.8)

project(TGASdk_test)

set(SOURCE_EXE main.cpp)

set(RuntimeOutputDir ${CMAKE_BINARY_DIR}../../exe)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${RuntimeOutputDir})


include_directories(tgasdk/include)

add_executable(TGASdk_test ${SOURCE_EXE})

add_subdirectory(tgasdk)

target_link_libraries(TGASdk_test TGASdk)	