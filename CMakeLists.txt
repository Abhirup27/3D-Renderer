cmake_minimum_required(VERSION 3.16)
project(OpenGLRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags to handle warnings
if(MSVC)
    add_compile_options(/W3 /wd4244 /wd4267 /wd4706 /wd4996 /wd4701)
else()
    add_compile_options(-Wall -Wno-dangling-reference -Wno-deprecated-declarations)
endif()

# Function to download and extract dependencies
function(download_and_extract URL DEST)
    if(NOT EXISTS ${DEST})
        message(STATUS "Downloading ${URL} to ${DEST}")
        file(DOWNLOAD ${URL} ${CMAKE_BINARY_DIR}/download.zip
            SHOW_PROGRESS
            STATUS DOWNLOAD_STATUS
        )
        file(ARCHIVE_EXTRACT INPUT ${CMAKE_BINARY_DIR}/download.zip
            DESTINATION ${DEST}
        )
        file(REMOVE ${CMAKE_BINARY_DIR}/download.zip)
    endif()
endfunction()

# Ensure dependencies directory exists
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/libs)
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
endif()

# Download dependencies
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/glfw)
    download_and_extract(
        "https://github.com/glfw/glfw/archive/refs/tags/3.3.8.zip"
        ${CMAKE_SOURCE_DIR}/libs/glfw
    )
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/glm)
    download_and_extract(
        "https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip"
        ${CMAKE_SOURCE_DIR}/libs/glm
    )
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/assimp)
    download_and_extract(
        "https://github.com/assimp/assimp/archive/refs/tags/v5.2.5.zip"
        ${CMAKE_SOURCE_DIR}/libs/assimp
    )
endif()

if(NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/glad)
    message(WARNING "Please generate GLAD files from https://glad.dav1d.de/ and place them in libs/glad")
endif()

# GLFW Configuration
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glfw/glfw-3.3.8 ${CMAKE_BINARY_DIR}/glfw)

# Assimp Configuration
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_DOUBLE_PRECISION OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

# Enable only the importers you need
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "" FORCE)

# Add compile definitions for Assimp
add_definitions(
    -DASSIMP_BUILD_NO_3DS_IMPORTER
    -DASSIMP_BUILD_NO_MD3_IMPORTER
    -DASSIMP_BUILD_NO_MDL_IMPORTER
    -DASSIMP_BUILD_NO_MD2_IMPORTER
    -DASSIMP_BUILD_NO_PLY_IMPORTER
    -DASSIMP_BUILD_NO_ASE_IMPORTER
    -DASSIMP_BUILD_NO_HMP_IMPORTER
    -DASSIMP_BUILD_NO_SMD_IMPORTER
    -DASSIMP_BUILD_NO_MDC_IMPORTER
    -DASSIMP_BUILD_NO_MD5_IMPORTER
    -DASSIMP_BUILD_NO_STL_IMPORTER
    -DASSIMP_BUILD_NO_LWO_IMPORTER
    -DASSIMP_BUILD_NO_DXF_IMPORTER
    -DASSIMP_BUILD_NO_NFF_IMPORTER
    -DASSIMP_BUILD_NO_RAW_IMPORTER
    -DASSIMP_BUILD_NO_OFF_IMPORTER
    -DASSIMP_BUILD_NO_AC_IMPORTER
    -DASSIMP_BUILD_NO_BVH_IMPORTER
    -DASSIMP_BUILD_NO_IRRMESH_IMPORTER
    -DASSIMP_BUILD_NO_IRR_IMPORTER
    -DASSIMP_BUILD_NO_Q3D_IMPORTER
    -DASSIMP_BUILD_NO_B3D_IMPORTER
    -DASSIMP_BUILD_NO_COLLADA_IMPORTER
    -DASSIMP_BUILD_NO_TERRAGEN_IMPORTER
    -DASSIMP_BUILD_NO_CSM_IMPORTER
    -DASSIMP_BUILD_NO_3D_IMPORTER
    -DASSIMP_BUILD_NO_LWS_IMPORTER
    -DASSIMP_BUILD_NO_OGRE_IMPORTER
    -DASSIMP_BUILD_NO_OPENGEX_IMPORTER
    -DASSIMP_BUILD_NO_MS3D_IMPORTER
    -DASSIMP_BUILD_NO_COB_IMPORTER
    -DASSIMP_BUILD_NO_BLEND_IMPORTER
    -DASSIMP_BUILD_NO_Q3BSP_IMPORTER
    -DASSIMP_BUILD_NO_NDO_IMPORTER
    -DASSIMP_BUILD_NO_IFC_IMPORTER
    -DASSIMP_BUILD_NO_XGL_IMPORTER
)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/assimp/assimp-5.2.5 ${CMAKE_BINARY_DIR}/assimp)

# Renderer Configuration
add_executable(Renderer)

# Add source files
file(GLOB_RECURSE RENDERER_SOURCES
    src/*.cpp
    src/*.hpp
    src/*.h
    src/*.c
)
target_sources(Renderer PRIVATE ${RENDERER_SOURCES}  ${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c)

# Include directories
target_include_directories(Renderer PRIVATE
    ${CMAKE_SOURCE_DIR}/src  # Add this to allow includes from src directory
    ${CMAKE_SOURCE_DIR}/libs/glfw/glfw-3.3.8/include
    ${CMAKE_SOURCE_DIR}/libs/glad/include
    ${CMAKE_SOURCE_DIR}/libs/glm
    ${CMAKE_SOURCE_DIR}/libs/assimp/assimp-5.2.5/include
)

target_link_libraries(Renderer PRIVATE glfw assimp)

if(UNIX)
    target_link_libraries(Renderer PRIVATE
        dl
        pthread
        X11
        Xrandr
        Xi
        GL
        z
    )
elseif(WIN32)
    target_link_libraries(Renderer PRIVATE opengl32)
endif()

# Copy shader files to build directory
file(GLOB SHADER_FILES ${CMAKE_SOURCE_DIR}/shaders/*)
file(COPY ${SHADER_FILES} DESTINATION ${CMAKE_BINARY_DIR}/shaders)

# Set build configurations
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Renderer PRIVATE DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
else()
    target_compile_definitions(Renderer PRIVATE NDEBUG)
    set(CMAKE_BUILD_TYPE Release)
endif()