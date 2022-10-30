cmake_minimum_required (VERSION 3.5.0)

set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE INTERNAL "" FORCE)

# Project name
project (gamebase)

if (WIN32)
  SET(SDL2_DIR "../SDL2/cmake")
  SET(SDL2_IMAGE_DIR "../SDL2_image/cmake")
endif()

find_package (SDL2 REQUIRED)
find_package (SDL2_IMAGE REQUIRED)

# Include SDL2 support for cmake

message(STATUS  ${SDL2_IMAGE_INCLUDE_DIR})
message(STATUS  ${SDL2_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIR})

# Include header files
include_directories (graphics)

set(SOURCES
   ${PROJECT_SOURCE_DIR}/main.cpp
   ${PROJECT_SOURCE_DIR}/app/baseapp.cpp
   ${PROJECT_SOURCE_DIR}/app/baseapp.h
   ${PROJECT_SOURCE_DIR}/graphics/graphics.cpp
   ${PROJECT_SOURCE_DIR}/graphics/graphics.h

   ${PROJECT_SOURCE_DIR}/snake/snake.h
   )
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
   SDL2::SDL2
   SDL2_image::SDL2_image
   )

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

if(WIN32)
    get_target_property(SDL2_LIBRARY SDL2::SDL2 IMPORTED_LOCATION)
    get_filename_component(SDL2_LIBRARY_NAME "${SDL2_LIBRARY}" NAME)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        MAIN_DEPENDENCY "${SDL2_LIBRARY}"
        BYPRODUCTS "${SDL2_LIBRARY_NAME}"
        COMMENT "Copying SDL2 DLL"
        COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_LIBRARY}" "${CMAKE_BINARY_DIR}/Debug/${SDL2_LIBRARY_NAME}"
    )

    get_target_property(SDL2_IMAGE_LIBRARY SDL2_image::SDL2_image IMPORTED_LOCATION)
    get_filename_component(SDL2_IMAGE_LIBRARY_NAME "${SDL2_IMAGE_LIBRARY}" NAME)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        MAIN_DEPENDENCY "${SDL2_IMAGE_LIBRARY}"
        BYPRODUCTS "${SDL2_IMAGE_LIBRARY_NAME}"
        COMMENT "Copying SDL2_image DLL"
        COMMAND "${CMAKE_COMMAND}" -E copy "${SDL2_IMAGE_LIBRARY}" "${CMAKE_BINARY_DIR}/Debug/${SDL2_IMAGE_LIBRARY_NAME}"
    )    
endif()