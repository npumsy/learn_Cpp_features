#include <iostream>
#include <memory>
#include <string>
#include <vector>
/*
三种智能指针的核心区别：
    std::unique_ptr<T>：独占所有权，不可拷贝，可移动。
    std::shared_ptr<T>：共享所有权，引用计数。
    std::weak_ptr<T>：配合 shared_ptr，解决循环引用。 
从C++11升级到C++14，以支持std::make_unique函数。
   */

// 简单的资源类，用于演示智能指针
class Resource {
private:
    std::string name_;
    int value_;

public:
    Resource(const std::string& name, int value) : name_(name), value_(value) {
        std::cout << "Resource创建: " << name_ << " (" << value_ << ")" << std::endl;
    }

    ~Resource() {
        std::cout << "Resource销毁: " << name_ << " (" << value_ << ")" << std::endl;
    }

    void set_value(int value) { value_ = value; }
    int get_value() const { return value_; }
    const std::string& get_name() const { return name_; }
}; 

// 演示三种智能指针的基础用法对比
void demonstrate_basic_usage() {
    std::cout << "\n===== 基础用法对比 =====" << std::endl;
    
// unique_ptr: 独占所有权
std::unique_ptr<Resource> unique = std::make_unique<Resource>("UniqueResource", 100);
// auto unique2 = unique;  // 编译错误，unique_ptr不能复制
auto unique2 = std::move(unique);  // 移动语义，unique2获得所有权，unique为空
std::cout << "unique_ptr: 独占所有权，不能复制，只能移动" << std::endl;

// shared_ptr: 共享所有权
std::shared_ptr<Resource> shared1 = std::make_shared<Resource>("SharedResource", 200);
std::shared_ptr<Resource> shared2 = shared1;  // 复制，引用计数增加到2
std::cout << "shared_ptr: 共享所有权，引用计数: " << shared1.use_count() << std::endl;
    
    // weak_ptr: 弱引用，不增加引用计数
    std::weak_ptr<Resource> weak = shared1;  // 弱引用，引用计数仍为2
    std::cout << "weak_ptr: 弱引用，不增加引用计数: " << shared1.use_count() << std::endl;
    
    // 访问资源
    std::cout << "unique_ptr访问资源: " << unique->get_name() << " = " << unique->get_value() << std::endl;
    std::cout << "shared_ptr访问资源: " << shared1->get_name() << " = " << shared1->get_value() << std::endl;
    
    // weak_ptr需要先lock转换为shared_ptr才能访问
    if (auto temp = weak.lock()) {
        std::cout << "weak_ptr通过lock()访问资源: " << temp->get_name() << " = " << temp->get_value() << std::endl;
    }
} 

// 演示所有权转移
void demonstrate_ownership_transfer() {
    std::cout << "\n===== 所有权转移对比 =====" << std::endl;
    
    // unique_ptr的所有权转移（必须使用std::move）
    std::unique_ptr<Resource> unique1 = std::make_unique<Resource>("UniqueTransfer", 300);
    std::unique_ptr<Resource> unique2 = std::move(unique1);  // 所有权转移
    std::cout << "unique_ptr所有权转移后，原指针是否为空: " << (unique1 ? "否" : "是") << std::endl;
    
    // shared_ptr的所有权共享（简单复制）
    std::shared_ptr<Resource> shared1 = std::make_shared<Resource>("SharedCopy", 400);
    std::shared_ptr<Resource> shared2 = shared1;  // 共享所有权
    std::cout << "shared_ptr共享所有权后的引用计数: " << shared1.use_count() << std::endl;
    
    // weak_ptr的所有权不影响
    std::weak_ptr<Resource> weak = shared1;
    shared1.reset();  // 释放shared1的所有权，但资源不会被销毁
    std::cout << "shared1重置后，weak_ptr是否有效: " << (!weak.expired() ? "是" : "否") << std::endl;
}

// 演示在容器中的使用
void demonstrate_container_usage() {
    std::cout << "\n===== 在容器中的使用对比 =====" << std::endl;
    
    // unique_ptr在容器中（需要移动语义）
    std::vector<std::unique_ptr<Resource>> unique_vec;
    unique_vec.push_back(std::make_unique<Resource>("UniqueInVector1", 500));
    unique_vec.push_back(std::make_unique<Resource>("UniqueInVector2", 600));
    std::cout << "unique_ptr在vector中的数量: " << unique_vec.size() << std::endl;
    
    // shared_ptr在容器中（直接复制）
    std::vector<std::shared_ptr<Resource>> shared_vec;
    auto shared = std::make_shared<Resource>("SharedInVector", 700);
    shared_vec.push_back(shared);
    shared_vec.push_back(shared);  // 同一个资源的多个引用
    std::cout << "shared_ptr在vector中引用计数: " << shared.use_count() << std::endl;
    
    // weak_ptr通常不直接存储在容器中，而是作为观察者
}

// 演示循环引用问题及解决方法
void demonstrate_cycle_reference() {
    std::cout << "\n===== 循环引用问题及解决 =====" << std::endl;
    
    // 前向声明
    struct Node;
    
    // 使用shared_ptr可能导致的循环引用
    struct Node {
        std::string name;
        std::shared_ptr<Node> next;  // 强引用
        
        Node(const std::string& n) : name(n) {
            std::cout << "Node创建: " << name << std::endl;
        }
        
        ~Node() {
            std::cout << "Node销毁: " << name << std::endl;
        }
    };
    
    {  // 新作用域
        // 创建循环引用
        auto node1 = std::make_shared<Node>("Node1");
        auto node2 = std::make_shared<Node>("Node2");
        
        node1->next = node2;
        node2->next = node1;  // 循环引用
        
        std::cout << "循环引用创建后，node1引用计数: " << node1.use_count() << std::endl;
        std::cout << "循环引用创建后，node2引用计数: " << node2.use_count() << std::endl;
        
        std::cout << "离开作用域，但由于循环引用，节点不会被销毁！" << std::endl;
    }
    
    // 使用weak_ptr解决循环引用
    struct WeakNode {
        std::string name;
        std::weak_ptr<WeakNode> next;  // 使用弱引用
        
        WeakNode(const std::string& n) : name(n) {
            std::cout << "WeakNode创建: " << name << std::endl;
        }
        
        ~WeakNode() {
            std::cout << "WeakNode销毁: " << name << std::endl;
        }
    };
    
    {  // 新作用域
        auto weak_node1 = std::make_shared<WeakNode>("WeakNode1");
        auto weak_node2 = std::make_shared<WeakNode>("WeakNode2");
        
        weak_node1->next = weak_node2;
        weak_node2->next = weak_node1;  // 不会形成强引用循环
        
        std::cout << "使用weak_ptr后，weak_node1引用计数: " << weak_node1.use_count() << std::endl;
        std::cout << "使用weak_ptr后，weak_node2引用计数: " << weak_node2.use_count() << std::endl;
        
        std::cout << "离开作用域，节点将被正确销毁！" << std::endl;
    }
}

// 总结三种智能指针的适用场景
void summarize_best_practices() {
    std::cout << "\n===== 智能指针最佳实践总结 =====" << std::endl;
    std::cout << "\n【unique_ptr】" << std::endl;
    std::cout << "- 独占所有权，适合大多数场景" << std::endl;
    std::cout << "- 性能最优，无引用计数开销" << std::endl;
    std::cout << "- 适合管理独占资源或工厂函数返回值" << std::endl;
    std::cout << "- 推荐优先使用" << std::endl;
    
    std::cout << "\n【shared_ptr】" << std::endl;
    std::cout << "- 共享所有权，需要引用计数" << std::endl;
    std::cout << "- 适合需要多个对象共享同一个资源的场景" << std::endl;
    std::cout << "- 有一定性能开销（引用计数的原子操作）" << std::endl;
    
    std::cout << "\n【weak_ptr】" << std::endl;
    std::cout << "- 不拥有资源，解决循环引用问题" << std::endl;
    std::cout << "- 适合观察者模式" << std::endl;
    std::cout << "- 不能直接访问资源，需要先lock()" << std::endl;
    
    std::cout << "\n选择原则：" << std::endl;
    std::cout << "1. 优先考虑unique_ptr（独占所有权）" << std::endl;
    std::cout << "2. 如需共享所有权，使用shared_ptr" << std::endl;
    std::cout << "3. 遇到循环引用，使用weak_ptr" << std::endl;
} 

int main() {
    std::cout << "===== C++智能指针综合对比示例 =====" << std::endl;
    
    demonstrate_basic_usage();
    // demonstrate_ownership_transfer();
    // demonstrate_container_usage();
    // demonstrate_cycle_reference();
    summarize_best_practices();
    
    std::cout << "\n===== 程序结束，所有智能指针管理的资源将被自动释放 =====" << std::endl;
    
    return 0;
}