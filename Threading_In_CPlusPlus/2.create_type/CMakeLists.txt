cmake_minimum_required(VERSION 3.10)
project(concurrency_create_type)

# 设置构建输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dev)

# 添加调试支持
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建可执行文件
add_executable(4.no_static_member_function 4.no_static_member_function.cpp)
add_executable(2.lambda_function 2.lambda_function.cpp)
add_executable(1.function_pointer 1.function_pointer.cpp)
add_executable(3.functor 3.functor.cpp)
add_executable(5.static_member_function 5.static_member_function.cpp)

# 链接线程库
if(WIN32)
    target_link_libraries(4.no_static_member_function PRIVATE pthread)
    target_link_libraries(2.lambda_function PRIVATE pthread)
    target_link_libraries(1.function_pointer PRIVATE pthread)
    target_link_libraries(3.functor PRIVATE pthread)
    target_link_libraries(5.static_member_function PRIVATE pthread)
else()
    target_link_libraries(4.no_static_member_function PRIVATE pthread)
    target_link_libraries(2.lambda_function PRIVATE pthread)
    target_link_libraries(1.function_pointer PRIVATE pthread)
    target_link_libraries(3.functor PRIVATE pthread)
    target_link_libraries(5.static_member_function PRIVATE pthread)
endif()