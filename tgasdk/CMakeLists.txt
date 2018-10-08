project(TGASdk)

set(SOURCE_LIB "sources/TGA.cpp" "sources/TGAColorMapData.cpp" "sources/TGAHeader.cpp" "sources/TGAImageData.cpp" "sources/TGAImageID.cpp" "sources/TGAVariable.cpp")

set(HEADERS_LIB "sources/TGAColorMapData.h" "sources/TGAFiler.hpp" "sources/TGAImageData.h" "sources/TGAImageID.h" "sources/TGAVariable.h" "include/TGA.h" "include/TGAEnum.h" "include/TGAExports.h" "include/TGAFile.h" "include/TGAHeader.h" "include/TGAVersion.h" "include/TGAError.hpp")


set(RuntimeOutputDir ${CMAKE_BINARY_DIR}../../exe)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${RuntimeOutputDir})

include_directories("include/")

add_definitions(-DTGA_EXPORTS)

add_library(TGASdk SHARED ${SOURCE_LIB} ${HEADERS_LIB})