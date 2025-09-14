#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

// 一个简单的类，用于演示shared_ptr
class Person {
private:
    std::string name_;
    int age_;

public:
    Person(const std::string& name, int age) : name_(name), age_(age) {
        std::cout << "Person构造函数: " << name_ << " (" << age_ << ")" << std::endl;
    }

    ~Person() {
        std::cout << "Person析构函数: " << name_ << " (" << age_ << ")" << std::endl;
    }

    void birthday() {
        ++age_;
        std::cout << name_ << " 过生日了！现在 " << age_ << " 岁" << std::endl;
    }

    void introduce() const {
        std::cout << "大家好，我是 " << name_ << ", 今年 " << age_ << " 岁" << std::endl;
    }
};

// 自定义删除器函数
void custom_deleter(Person* p) {
    std::cout << "自定义删除器被调用" << std::endl;
    delete p;
}

// 用于测试shared_ptr的线程安全性
class Counter {
private:
    // std::mutex mtx_;
    mutable std::mutex mtx_; // 确保在 const 成员函数中也能锁定互斥锁
    int count_;

public:
    Counter() : count_(0) {}

    void increment() {
        std::lock_guard<std::mutex> lock(mtx_);
        ++count_;
    }

    int get_count() const {
        // - 在 const 成员函数中，所有成员变量都被视为 const
        // - 但是 std::lock_guard 需要获取互斥锁的非 const 引用（因为锁定操作会修改互斥锁的状态）
        // mutable 关键字专门用于允许在 const 成员函数中修改某些成员变量。
        std::lock_guard<std::mutex> lock(mtx_);
        return count_;
    }
};

// 线程函数，共享同一个shared_ptr
void thread_function(std::shared_ptr<Counter> counter, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        counter->increment();
    }
}

int main() {
    std::cout << "===== shared_ptr智能指针示例 =====" << std::endl;

    // 1. 创建和基本使用
    std::cout << "\n1. shared_ptr的创建和基本使用:" << std::endl;
    std::shared_ptr<Person> p1(new Person("张三", 25)); // 使用new构造
    p1->introduce();
    p1->birthday();
    
    // 2. 使用make_shared（推荐的方式）
    std::cout << "\n2. 使用make_shared创建（推荐方式）:" << std::endl;
    auto p2 = std::make_shared<Person>("李四", 30);
    p2->introduce();
    
    // 3. 共享所有权
    std::cout << "\n3. 共享所有权:" << std::endl;
    std::shared_ptr<Person> p3 = p1; // 两个指针共享同一个对象
    std::cout << "p1的引用计数: " << p1.use_count() << std::endl;
    std::cout << "p3的引用计数: " << p3.use_count() << std::endl;
    p3->introduce(); // 通过p3访问对象
    
    // 4. 自定义删除器
    std::cout << "\n4. 自定义删除器:" << std::endl;
    std::shared_ptr<Person> p4(new Person("王五", 35), custom_deleter);
    p4->introduce();
    
    // 5. 重置shared_ptr
    std::cout << "\n5. 重置shared_ptr:" << std::endl;
    std::cout << "重置前p1的引用计数: " << p1.use_count() << std::endl;
    p1.reset(); // 重置p1，引用计数减1
    std::cout << "重置后p3的引用计数: " << p3.use_count() << std::endl;
    if (p1) {
        p1->introduce(); // 不会执行，因为p1已经被重置
    } else {
        std::cout << "p1已经不指向任何对象" << std::endl;
    }
    
    // 6. shared_ptr在容器中的使用
    std::cout << "\n6. shared_ptr在容器中的使用:" << std::endl;
    std::vector<std::shared_ptr<Person>> people;
    people.push_back(p2);
    people.push_back(p3);
    people.push_back(p4);
    
    std::cout << "容器添加后p2的引用计数: " << p2.use_count() << std::endl;
    std::cout << "容器添加后p3的引用计数: " << p3.use_count() << std::endl;
    std::cout << "容器添加后p4的引用计数: " << p4.use_count() << std::endl;
    
    // 遍历容器中的元素
    for (const auto& person : people) {
        person->introduce();
    }
    
    // 7. shared_ptr的线程安全性测试
    std::cout << "\n7. shared_ptr的线程安全性测试:" << std::endl;
    auto counter = std::make_shared<Counter>();
    std::cout << "初始计数: " << counter->get_count() << std::endl;
    
    // 创建多个线程，共享同一个Counter对象
    std::vector<std::thread> threads;
    const int num_threads = 5;
    const int iterations_per_thread = 1000;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(thread_function, counter, iterations_per_thread);
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "预期计数: " << num_threads * iterations_per_thread << std::endl;
    std::cout << "实际计数: " << counter->get_count() << std::endl;
    
    // 8. shared_ptr的常见陷阱
    std::cout << "\n8. shared_ptr的常见陷阱:" << std::endl;
    std::cout << "- 避免循环引用（使用weak_ptr解决）" << std::endl;
    std::cout << "- 不要用同一个原始指针初始化多个shared_ptr" << std::endl;
    std::cout << "- 避免管理不是通过new分配的内存" << std::endl;
    std::cout << "- make_shared比直接使用new更高效" << std::endl;
    
    std::cout << "\n===== shared_ptr智能指针示例结束 =====" << std::endl;
    
    // 所有shared_ptr离开作用域时，引用计数为0的对象会被自动删除
    
    return 0;
}