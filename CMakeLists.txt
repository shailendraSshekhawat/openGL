cmake_minimum_required(VERSION 3.27.4)

project(openGL VERSION 0.1.0)

include_directories(src, src/vendor)
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/Renderer.h 
    src/Renderer.cpp 
    src/VertexBuffer.h 
    src/VertexBuffer.cpp
    src/IndexBuffer.h
    src/IndexBuffer.cpp
    src/VertexArray.h
    src/VertexBufferLayout.h
    src/VertexArray.cpp
    src/Shader.h
    src/Shader.cpp
    src/vendor/stb_image/stb_image.cpp
    src/vendor/stb_image/stb_image.h
    src/Texture.h
    src/Texture.cpp
    

    
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib)
target_link_libraries(${PROJECT_NAME} glfw glad)
