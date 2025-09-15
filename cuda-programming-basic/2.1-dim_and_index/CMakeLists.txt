cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(dim_and_index LANGUAGES CXX CUDA)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置CUDA标准
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# 查找CUDA包
find_package(CUDA REQUIRED)

# 添加包含目录
include_directories(
    ${CUDA_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 收集源文件
file(GLOB SOURCES "src/*.cu")

# 创建可执行文件
cuda_add_executable(${PROJECT_NAME} ${SOURCES})

# 添加链接库
target_link_libraries(${PROJECT_NAME}
    ${CUDA_LIBRARIES}
)

# 设置CUDA编译选项
set_target_properties(${PROJECT_NAME} PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)