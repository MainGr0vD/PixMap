cmake_minimum_required(VERSION 3.14)

PROJECT(PixParser)

SET(DESTINATION_DEBUG   "${PixParser_SOURCE_DIR}/Build/Debug/")
SET(DESTINATION_RELEASE "${PixParser_SOURCE_DIR}/Build/Release/")

SET(FI_DLL_FILE  "${PixParser_SOURCE_DIR}/FreeImageDLL/x64/FreeImage.dll")
SET(FI_LIB_FILE "${PixParser_SOURCE_DIR}/FreeImageDLL/x64/FreeImage.lib")

IF(EXISTS ${FI_DLL_FILE})
    file(INSTALL ${FI_DLL_FILE}  DESTINATION "${DESTINATION_DEBUG}")
ELSE()
    message(WARNING "File '${FI_DLL_FILE}' not found")
ENDIF()
IF(EXISTS ${FI_LIB_FILE})
    file(INSTALL ${FI_LIB_FILE}  DESTINATION "${DESTINATION_DEBUG}")
ELSE()
    message(WARNING "File '${FI_LIB_FILE}' not found")
ENDIF()

IF(EXISTS ${FI_DLL_FILE})
    file(INSTALL ${FI_DLL_FILE}  DESTINATION "${DESTINATION_RELEASE}")
ELSE()
    message(WARNING "File '${FI_DLL_FILE}' not found")
ENDIF()
IF(EXISTS ${FI_LIB_FILE})
    file(INSTALL ${FI_LIB_FILE}  DESTINATION "${DESTINATION_RELEASE}")
ELSE()
    message(WARNING "File '${FI_LIB_FILE}' not found")
ENDIF()


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SRC source/*.cpp source/*.h)
include_directories(source)

set(PROJECT_SOURCES
    ${SRC}
)
set(FREE_IMAGE "${PixParser_SOURCE_DIR}/FreeImageDLL/x64/")
add_executable(PixParser ${PROJECT_SOURCES})
target_include_directories(PixParser PRIVATE ${FREE_IMAGE})
target_link_libraries(PixParser PRIVATE optimized;${FI_LIB_FILE} ;debug;${FI_LIB_FILE} )


