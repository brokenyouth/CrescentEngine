cmake_minimum_required(VERSION 3.19)
project(CrescentEngine)

# Settings
set(CMAKE_CXX_STANDARD 20)

# Sub-projects
add_subdirectory(glfw)
add_subdirectory(glew)
add_subdirectory(assimp)
add_subdirectory(CrescentEngine)


target_include_directories(CrescentEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(CrescentEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)
target_include_directories(CrescentEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/assimp/include)
target_include_directories(CrescentEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

