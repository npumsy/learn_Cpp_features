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


# 创建可执行文件
cuda_add_executable(${PROJECT_NAME} "src/print_index.cu")

# 添加链接库
target_link_libraries(${PROJECT_NAME}
    ${CUDA_LIBRARIES}
)

# 设置CUDA编译选项
set_target_properties(${PROJECT_NAME} PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

# 创建可执行文件
cuda_add_executable(add_test "src/add_kernal.cu")
target_link_libraries(add_test    ${CUDA_LIBRARIES})
set_target_properties(add_test PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)