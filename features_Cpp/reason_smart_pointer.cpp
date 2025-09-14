#include <iostream>
#include <memory>
#include <vector>

// 示例1: 忘记释放内存
void leak1() {
    int* data = new int[1000];  // 分配内存
    // ... 使用data
    // 忘记调用 delete[] data;  // 内存泄漏
}

// 示例1的智能指针版本
void no_leak1() {
    std::unique_ptr<int[]> data = std::make_unique<int[]>(1000);  // 智能指针自动管理
    // ... 使用data
    // 离开作用域时自动释放，无需手动delete
}

// 示例2: 提前返回导致内存泄漏
void leak2(bool condition) {
    int* data = new int[1000];
    if (condition) {
        return;  // 提前返回，忘记释放data，内存泄漏
    }
    delete[] data;  // 条件不满足时才会释放
}

// 示例2的智能指针版本
void no_leak2(bool condition) {
    std::unique_ptr<int[]> data = std::make_unique<int[]>(1000);
    if (condition) {
        return;  // 提前返回，但智能指针仍会自动释放资源
    }
    // 无需手动delete
}

// 示例3: 异常导致的内存泄漏
void leak3() {
    int* data = new int[1000];
    try {
        throw std::runtime_error("异常发生");
    } catch (...) {
        // 没有在catch块中释放内存，内存泄漏
        throw;  // 重新抛出异常
    }
    delete[] data;  // 异常发生时这行不会执行
}

// 示例3的智能指针版本
void no_leak3() {
    std::unique_ptr<int[]> data = std::make_unique<int[]>(1000);
    try {
        throw std::runtime_error("异常发生");
    } catch (...) {
        // 即使抛出异常，智能指针也会自动释放内存
        throw;
    }
    // 无需手动delete
}

// 示例4: 循环引用问题
class Node {
public:
    std::shared_ptr<Node> next;  // shared_ptr导致循环引用
    Node() { std::cout << "Node构造" << std::endl; }
    ~Node() { std::cout << "Node析构" << std::endl; }
};

void leak4() {
    auto node1 = std::make_shared<Node>();
    auto node2 = std::make_shared<Node>();
    node1->next = node2;  // node1引用node2
    node2->next = node1;  // node2引用node1，形成循环引用
    // 即使离开作用域，由于循环引用，引用计数不会降为0，内存泄漏
}

// 示例4的智能指针解决方案
class NodeFix {
public:
    std::weak_ptr<NodeFix> next;  // 使用weak_ptr打破循环引用
    NodeFix() { std::cout << "NodeFix构造" << std::endl; }
    ~NodeFix() { std::cout << "NodeFix析构" << std::endl; }
};

void no_leak4() {
    auto node1 = std::make_shared<NodeFix>();
    auto node2 = std::make_shared<NodeFix>();
    node1->next = node2;  // weak_ptr不增加引用计数
    node2->next = node1;  // 打破循环引用
    // 离开作用域时，引用计数降为0，资源被正确释放
}

// 示例5: 容器中的指针未释放
void leak5() {
    std::vector<int*> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(new int(i));  // 向容器添加动态分配的指针
    }
    // vec被销毁时，容器中的指针指向的内存未被释放，内存泄漏
}

// 示例5的智能指针版本
void no_leak5() {
    std::vector<std::unique_ptr<int>> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(std::make_unique<int>(i));  // 容器存储智能指针
    }
    // vec被销毁时，所有智能指针自动释放其管理的资源
}

int main() {
    std::cout << "=== 智能指针使用理由演示 ===" << std::endl;
    
    std::cout << "\n1. 忘记释放内存：" << std::endl;
    leak1();
    no_leak1();
    
    std::cout << "\n2. 提前返回导致内存泄漏：" << std::endl;
    leak2(true);
    no_leak2(true);
    
    std::cout << "\n3. 异常导致的内存泄漏：" << std::endl;
    try { leak3(); } catch (...) {}
    try { no_leak3(); } catch (...) {}
    
    std::cout << "\n4. 循环引用问题：" << std::endl;
    leak4();  // 注意：这里不会输出析构信息，说明内存泄漏
    std::cout << "解决循环引用：" << std::endl;
    no_leak4();  // 会输出析构信息，说明资源被正确释放
    
    std::cout << "\n5. 容器中的指针未释放：" << std::endl;
    leak5();
    no_leak5();
    
    std::cout << "\n=== 演示结束 ===" << std::endl;
    return 0;
}