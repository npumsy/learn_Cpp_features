cmake_minimum_required(VERSION 3.10)
project(concurrency_thread)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加调试支持
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# 创建可执行文件
add_executable(intro intro.cpp)
add_executable(thread thread.cpp)

# 链接线程库
if(WIN32)
    target_link_libraries(intro PRIVATE pthread)
    target_link_libraries(thread PRIVATE pthread)
else()
    target_link_libraries(intro PRIVATE pthread)
    target_link_libraries(thread PRIVATE pthread)
endif()