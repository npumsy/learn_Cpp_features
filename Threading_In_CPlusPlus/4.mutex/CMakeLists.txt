cmake_minimum_required(VERSION 3.10)
project(concurrency_mutex)

# 设置构建输出目录
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dev)

# 添加调试支持
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建可执行文件
add_executable(critical_section critical_section.cpp)

# 链接线程库
if(WIN32)
    target_link_libraries(critical_section PRIVATE pthread)
else()
    target_link_libraries(critical_section PRIVATE pthread)
endif()