#include <iostream>
#include <string>
#include <vector>

// 演示移动语义的类
class Resource {
private:
    std::string* data_; // 大型资源指针
    size_t size_;       // 资源大小

public:
    // 默认构造函数
    Resource() : data_(nullptr), size_(0) {
        std::cout << "默认构造函数被调用" << std::endl;
    }

    // 带参数的构造函数
    explicit Resource(size_t size) : size_(size) {
        std::cout << "构造函数被调用，分配大小: " << size << std::endl;
        data_ = new std::string[size];
        for (size_t i = 0; i < size; ++i) {
            data_[i] = "Resource Data " + std::to_string(i);
        }
    }

    // 复制构造函数（深拷贝）
    Resource(const Resource& other) : size_(other.size_) {
        std::cout << "复制构造函数被调用（深拷贝）" << std::endl;
        data_ = new std::string[size_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // 复制赋值运算符
    Resource& operator=(const Resource& other) {
        std::cout << "复制赋值运算符被调用（深拷贝）" << std::endl;
        if (this != &other) {
            // 释放原有资源
            delete[] data_;
            
            // 分配新资源并复制数据
            size_ = other.size_;
            data_ = new std::string[size_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    // 移动构造函数
    Resource(Resource&& other) noexcept : data_(other.data_), size_(other.size_) {
        std::cout << "移动构造函数被调用" << std::endl;
        // 将源对象置为有效但不确定的状态
        other.data_ = nullptr;
        other.size_ = 0;
    }

    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        std::cout << "移动赋值运算符被调用" << std::endl;
        if (this != &other) {
            // 释放原有资源
            delete[] data_;
            
            // 获取源对象的资源
            data_ = other.data_;
            size_ = other.size_;
            
            // 将源对象置为有效但不确定的状态
            other.data_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // 析构函数
    ~Resource() {
        std::cout << "析构函数被调用，释放大小: " << size_ << std::endl;
        delete[] data_;
    }

    // 获取资源大小
    size_t size() const {
        return size_;
    }

    // 检查资源是否有效
    bool is_valid() const {
        return data_ != nullptr;
    }
};

// 返回大对象的函数，将触发移动语义
Resource create_large_resource() {
    std::cout << "创建大型资源对象" << std::endl;
    Resource res(1000); // 创建一个大资源
    return res; // 这里会发生移动（或者编译器优化）
}

int main() {
    std::cout << "===== 移动语义示例 =====" << std::endl;
    
    // 测试移动构造函数
    std::cout << "\n1. 测试移动构造函数:" << std::endl;
    Resource res1(5); // 创建一个资源对象
    Resource res2(std::move(res1)); // 使用移动构造函数
    std::cout << "res1是否有效: " << (res1.is_valid() ? "是" : "否") << std::endl;
    std::cout << "res2大小: " << res2.size() << std::endl;
    
    // 测试移动赋值运算符
    std::cout << "\n2. 测试移动赋值运算符:" << std::endl;
    Resource res3(10);
    Resource res4;
    res4 = std::move(res3); // 使用移动赋值运算符
    std::cout << "res3是否有效: " << (res3.is_valid() ? "是" : "否") << std::endl;
    std::cout << "res4大小: " << res4.size() << std::endl;
    
    // 测试从函数返回值移动
    std::cout << "\n3. 测试从函数返回值移动:" << std::endl;
    Resource res5 = create_large_resource();
    std::cout << "res5大小: " << res5.size() << std::endl;
    
    // 测试标准库容器中的移动语义
    std::cout << "\n4. 测试标准库容器中的移动语义:" << std::endl;
    std::vector<Resource> resources;
    std::cout << "向vector添加第一个元素（复制）" << std::endl;
    resources.push_back(res5); // 这里会发生复制，因为res5后续还要使用
    
    std::cout << "向vector添加第二个元素（移动）" << std::endl;
    resources.push_back(std::move(res5)); // 这里会发生移动
    std::cout << "res5是否有效: " << (res5.is_valid() ? "是" : "否") << std::endl;
    
    std::cout << "\n===== 移动语义示例结束 =====" << std::endl;
    
    // 移动语义的优势：
    // 1. 避免不必要的深拷贝，提高程序性能
    // 2. 特别适合处理大型资源（如动态分配的内存、文件句柄等）
    // 3. 使得临时对象的资源可以被有效利用，而不是被立即销毁
    // 4. 支持C++11中的标准库容器和算法更高效地工作
    
    return 0;
}