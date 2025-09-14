
# C++ 多线程编程示例

## 项目概述
本目录包含C++11多线程编程的基础示例代码，涵盖线程创建、参数传递、互斥锁、条件变量、原子操作、异步任务等多线程编程的核心概念和实现方法。

## 目录结构
```
cpp_multi_thread/
└── src/
    ├── async_future.cc # std::async和std::future使用示例
    ├── atomic_operator.cc # 原子操作示例
    ├── condition_variable.cc # 条件变量使用示例
    ├── promise.cc      # std::promise使用示例
    ├── thread_base.cc  # 线程创建的基础示例
    ├── thread_mutex.cc # 互斥锁使用示例
    ├── thread_once.cc  # 单例模式实现示例
```

## 核心示例说明

### 1. 线程基础（thread_base.cc）
演示了C++11中创建线程的三种基本方式：
- 使用普通函数作为线程入口
- 使用类的仿函数（operator()重载）作为线程入口
- 使用类的成员函数作为线程入口
同时展示了线程的join、detach和joinable状态检查。

### 3. 互斥锁（thread_mutex.cc）
演示了互斥锁的基本使用和死锁问题：
- 展示了错误的锁获取顺序如何导致死锁
- 展示了正确的锁获取顺序
- 展示了使用std::lock()函数同时锁定多个互斥量的方法
- 展示了lock_guard的使用方式

### 4. 单例模式（thread_once.cc）
使用互斥锁实现了线程安全的单例模式：
- 使用双重检查锁定模式（Double-Checked Locking Pattern）提高性能
- 使用GCCollect类实现单例对象的自动释放
- 演示了多线程环境下如何确保只创建一个实例

### 5. 原子操作（atomic_operator.cc）
演示了原子操作与互斥锁的性能对比：
- 使用普通计数器（非线程安全）与互斥锁保护的计数器
- 使用std::atomic实现线程安全的计数器
- 对比两种方式在多线程环境下的结果和性能差异

### 6. 条件变量（condition_variable.cc）
演示了条件变量在生产者-消费者模型中的应用：
- 使用std::condition_variable实现线程间的同步
- 展示了wait()和notify_one()函数的使用
- 讨论了条件变量使用中的一些注意事项和潜在问题

### 7. 异步任务（async_future.cc）
演示了std::async和std::future的使用：
- 创建异步任务并获取其返回结果
- 展示了不同启动策略（std::launch::async和std::launch::deferred）的区别

### 8. 线程通信（promise.cc）
演示了使用std::promise进行线程间通信：
- 在主线程中设置值
- 在子线程中获取该值
- 展示了线程间的数据传递机制
