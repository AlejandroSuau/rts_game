# Versión mínima de CMake requerida
cmake_minimum_required(VERSION 3.16)

# Nombre del proyecto
project(RTSGame LANGUAGES CXX)

# Configurar la versión estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurar el compilador
set(CMAKE_CXX_COMPILER clang++)

# Añadir directorios relevantes
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR})

# Include Raylib
set(PROJECT_RAYLIB_DIR ${CMAKE_SOURCE_DIR}/raylib/src)
include_directories(${PROJECT_RAYLIB_DIR})

# Encontrar automáticamente todos los archivos en src/
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

# Biblioteca raylib
set(RAYLIB_LIB ${CMAKE_SOURCE_DIR}/lib/libraylib.a)

# Crear el ejecutable
add_executable(rtsgame ${SOURCES})

# Enlazar las bibliotecas y frameworks necesarios
target_link_libraries(rtsgame PRIVATE ${RAYLIB_LIB}
    "-framework CoreVideo"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework GLUT"
    "-framework OpenGL"
)
