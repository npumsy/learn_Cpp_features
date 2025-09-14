cmake_minimum_required(VERSION 3.17)
project(cpp_multi_thread)

set(CMAKE_CXX_STANDARD 11)

# 按readme顺序为每个示例生成可执行文件
add_executable(thread_base thread_base.cc)
add_executable(thread_mutex thread_mutex.cc)
add_executable(thread_once thread_once.cc)
add_executable(atomic_operator atomic_operator.cc)
add_executable(condition_variable condition_variable.cc)
add_executable(async_future async_future.cc)
add_executable(promise promise.cc)