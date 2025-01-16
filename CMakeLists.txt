# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.16)

# Habilitar la generación de compile_commands.json
# Este archivo es útil para herramientas como clang-tidy o lenguaje servers (LSP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Nombre del proyecto
project(RTSGame LANGUAGES CXX)

# Configurar la versión estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Añadir directorios relevantes
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR})

# Include Raylib
set(PROJECT_RAYLIB_DIR ${CMAKE_SOURCE_DIR}/raylib/src)
include_directories(${PROJECT_RAYLIB_DIR})

# Encontrar automáticamente todos los archivos en src/
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

set(RAYLIB_DIR ${CMAKE_SOURCE_DIR}/raylib)
add_subdirectory(${RAYLIB_DIR} ${CMAKE_BINARY_DIR}/raylib)

# Crear el ejecutable
add_executable(rtsgame ${SOURCES})

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(rtsgame PRIVATE /W4 /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR 
        CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(rtsgame PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Configuraciones específicas del sistema operativo
if(WIN32)
    message(STATUS "Building for Windows")
    set(OS_SPECIFIC_LIBS
        -lwinmm
        -lgdi32
        -ldsound
    )
elseif(APPLE)
    message(STATUS "Building for macOS")
    set(OS_SPECIFIC_LIBS
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )
elseif(UNIX)
    message(STATUS "Building for Linux")
    set(OS_SPECIFIC_LIBS
        -lX11
        -lpthread
        -lGL
        -lm
        -ldl
    )
else()
    message(FATAL_ERROR "Unsupported operating system")
endif()

# Enlazar las bibliotecas y frameworks necesarios
target_link_libraries(
    rtsgame
    PRIVATE raylib
    ${OS_SPECIFIC_LIBS}
)
