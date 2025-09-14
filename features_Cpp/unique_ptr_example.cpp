#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 一个简单的类，用于演示unique_ptr
class Resource {
private:
    std::string name_;
    int value_;

public:
    Resource(const std::string& name, int value) : name_(name), value_(value) {
        std::cout << "Resource构造函数: " << name_ << " (" << value_ << ")" << std::endl;
    }

    ~Resource() {
        std::cout << "Resource析构函数: " << name_ << " (" << value_ << ")" << std::endl;
    }

    void set_value(int value) {
        value_ = value;
        std::cout << "设置" << name_ << "的值为: " << value_ << std::endl;
    }

    void display() const {
        std::cout << "Resource信息: " << name_ << " = " << value_ << std::endl;
    }
};

int main() {
    std::cout << "===== unique_ptr智能指针示例（初学者版）=====" << std::endl;
    std::cout << "// unique_ptr是独占所有权的智能指针，同一时间只能有一个unique_ptr指向某个对象" << std::endl;
    std::cout << "// 当unique_ptr离开作用域时，它所指向的对象会被自动删除" << std::endl;
    std::cout << "// 这是最常用的智能指针类型，适合大多数场景" << std::endl;

    // 1. 创建unique_ptr的基本方式
    std::cout << "\n1. 创建unique_ptr的基本方式:" << std::endl;
    
    // 方式1: 使用make_unique（C++14推荐的方式）
    std::cout << "\n- 使用make_unique创建（推荐方式，C++14及以上）:" << std::endl;
    auto ptr1 = std::make_unique<Resource>("资源A", 10);
    ptr1->display();
    
    // 方式2: 使用new（C++11兼容方式）
    std::cout << "\n- 使用new创建（C++11兼容方式）:" << std::endl;
    std::unique_ptr<Resource> ptr2(new Resource("资源B", 20));
    ptr2->display();

    // 2. unique_ptr的独占特性
    std::cout << "\n2. unique_ptr的独占特性（不能复制，只能移动）:" << std::endl;
    
    // 下面这行代码会编译错误，因为unique_ptr不能复制
    // std::unique_ptr<Resource> ptr3 = ptr1; // 编译错误
    
    // 正确的做法是使用移动语义
    std::cout << "\n- 使用std::move转移所有权:" << std::endl;
    std::unique_ptr<Resource> ptr3 = std::move(ptr1);
    
    // 转移后，ptr1不再拥有资源
    if (ptr1) {
        std::cout << "ptr1仍然有效" << std::endl;
    } else {
        std::cout << "ptr1已经不指向任何对象（所有权已转移）" << std::endl;
    }
    
    // ptr3现在拥有资源
    if (ptr3) {
        std::cout << "ptr3现在拥有资源: " << std::endl;
        ptr3->display();
    }

    // 3. 重置unique_ptr
    std::cout << "\n3. 重置unique_ptr（释放旧资源或指向新资源）:" << std::endl;
    
    // 释放当前资源
    std::cout << "\n- 释放当前资源（调用reset()无参数）:" << std::endl;
    ptr3.reset(); // 释放Resource("资源A", 10)
    
    if (!ptr3) {
        std::cout << "ptr3已被重置，不指向任何对象" << std::endl;
    }
    
    // 指向新资源
    std::cout << "\n- 指向新资源（调用reset()带参数）:" << std::endl;
    ptr3.reset(new Resource("资源C", 30));
    ptr3->display();

    // 4. 在容器中使用unique_ptr
    std::cout << "\n4. 在容器中使用unique_ptr（存储多个独占对象）:" << std::endl;
    std::vector<std::unique_ptr<Resource>> resources;
    
    // 添加元素到容器（需要使用std::move）
    resources.push_back(std::move(ptr2)); // ptr2不再拥有资源
    resources.push_back(std::move(ptr3)); // ptr3不再拥有资源
    resources.push_back(std::make_unique<Resource>("资源D", 40));
    
    // 遍历容器中的元素
    std::cout << "\n- 遍历容器中的资源: " << std::endl;
    for (const auto& res : resources) {
        res->display();
    }

    // 5. 从函数返回unique_ptr
    std::cout << "\n5. 从函数返回unique_ptr（自动移动语义）:" << std::endl;
    auto create_resource = [](const std::string& name, int value) {
        return std::make_unique<Resource>(name, value);
    };
    
    auto ptr4 = create_resource("返回的资源", 50);
    ptr4->display();

    // 6. 使用unique_ptr管理数组（自动处理delete[]）
    std::cout << "\n6. 使用unique_ptr管理数组（自动调用delete[]）:" << std::endl;
    std::unique_ptr<int[]> int_array(new int[5]);
    
    // 使用数组
    for (int i = 0; i < 5; ++i) {
        int_array[i] = i * 10;
        std::cout << "int_array[" << i << "] = " << int_array[i] << std::endl;
    }
    // 不需要手动释放数组，unique_ptr会自动处理

    // 7. unique_ptr的常见使用场景总结
    std::cout << "\n7. unique_ptr的常见使用场景（初学者须知）:" << std::endl;
    std::cout << "- 管理动态分配的单个对象（最常用场景）" << std::endl;
    std::cout << "- 作为工厂函数的返回类型" << std::endl;
    std::cout << "- 存储在容器中（如vector、list等）" << std::endl;
    std::cout << "- 管理对象的生命周期，避免内存泄漏" << std::endl;
    std::cout << "- 作为类成员，实现RAII原则" << std::endl;

    std::cout << "\n===== unique_ptr智能指针示例结束 =====" << std::endl;
    
    // 所有unique_ptr离开作用域时，它们管理的资源会被自动删除
    
    return 0;
}