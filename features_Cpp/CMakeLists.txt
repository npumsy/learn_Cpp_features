cmake_minimum_required(VERSION 3.10)
project(CppFeaturesExamples)

# 设置C++标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 创建示例可执行文件
add_executable(move_semantics move_semantics.cpp)

add_executable(shared_ptr_example shared_ptr_example.cpp)
# 添加线程支持
find_package(Threads REQUIRED)
target_link_libraries(shared_ptr_example Threads::Threads)

add_executable(functor_example functor_example.cpp)
add_executable(unique_ptr_example unique_ptr_example.cpp)

# RAII 资源创建即初始化
add_executable(move_copy_test move_copy_test.cpp)
add_executable(raii_move_test raii_move_test.cpp)
add_executable(smart_pointer_advantages smart_pointer_advantages.cpp)

add_executable(weak_ptr_example weak_ptr_example.cpp)
add_executable(smart_pointers_comparison smart_pointers_comparison.cpp)
add_executable(callable_objects_summary callable_objects_summary.cpp)