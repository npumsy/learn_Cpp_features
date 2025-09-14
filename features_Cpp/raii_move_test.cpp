#include <iostream>
#include <memory>
#include <utility>
#include <cstring>

// 修复并完善用户提供的XData类示例
class XData {
public:
    XData() {
        data_ = new char[1024];
    }
    XData(XData&& other) noexcept : data_(other.data_) {
        other.data_ = nullptr; 
    }
    ~XData() {
        delete[] data_;
        data_ = nullptr;
    }
    char* getData() { return data_; }
    
private:
    char* data_ = nullptr;
};

// // 使用int数组的RAII类示例
// class IntArray {
// public:
//     IntArray(size_t size) : size_(size) {
//         data_ = new int[size];
//         std::cout << "IntArray构造，分配大小为" << size_ << "的int数组" << std::endl;
//     }
    
//     // 移动构造函数
//     IntArray(IntArray&& other) noexcept : data_(other.data_), size_(other.size_) {
//         other.data_ = nullptr;
//         other.size_ = 0;
//         std::cout << "IntArray移动构造，转移资源所有权" << std::endl;
//     }
    
//     // 移动赋值运算符
//     IntArray& operator=(IntArray&& other) noexcept {
//         if (this != &other) {
//             delete[] data_;
//             data_ = other.data_;
//             size_ = other.size_;
//             other.data_ = nullptr;
//             other.size_ = 0;
//             std::cout << "IntArray移动赋值，转移资源所有权" << std::endl;
//         }
//         return *this;
//     }
    
//     // 禁用拷贝
//     IntArray(const IntArray&) = delete;
//     IntArray& operator=(const IntArray&) = delete;
    
//     ~IntArray() {
//         delete[] data_;
//         data_ = nullptr;
//         size_ = 0;
//         std::cout << "IntArray析构，释放int数组资源" << std::endl;
//     }
    
//     // 提供数组访问操作
//     int& operator[](size_t index) {
//         return data_[index];
//     }
    
//     size_t size() const { return size_; }
    
// private:
//     int* data_ = nullptr;
//     size_t size_ = 0;
// };

// 演示函数：返回XData对象（利用移动语义）
XData createXData() {
    XData data;
    strcpy(data.getData(), "Hello RAII!");
    return data;  // 返回值优化或移动语义
}

// // 演示函数：返回IntArray对象
// IntArray createIntArray(size_t size) {
//     IntArray arr(size);
//     for (size_t i = 0; i < size; ++i) {
//         arr[i] = static_cast<int>(i * 10);
//     }
//     return arr;  // 返回值优化或移动语义
// }

int main() {
    std::cout << "===== RAII优势演示 ======" << std::endl;
    
    std::cout << "\n--- 1. 手动管理堆内存 ---" << std::endl;
    // 手动管理内存需要显式delete，容易出错
    auto pdata = new char[1024];
    strcpy(pdata, "手动管理的内存");
    std::cout << "手动分配内存内容: " << pdata << std::endl;
    delete[] pdata;  // 必须手动释放，否则内存泄漏
    
    std::cout << "\n--- 2. 栈区资源的限制 ---" << std::endl;
    {
        char buf[1024];  // 栈区数组
        strcpy(buf, "栈区资源");
        std::cout << "栈区数组内容: " << buf << std::endl;
        
        // 以下代码无法编译通过，因为栈区资源不能移动
        // auto moved_buf = std::move(buf);  // 编译错误
        
        // 只能通过拷贝方式传递栈区资源内容
        char copied_buf[1024];
        strcpy(copied_buf, buf);
        std::cout << "拷贝的栈区数组内容: " << copied_buf << std::endl;
        
        // 离开作用域时，buf会被自动释放，但内容无法通过所有权转移保留
    }
    
    std::cout << "\n--- 3. 智能指针管理堆资源 ---" << std::endl;
    {
        auto pdata_smart = std::make_unique<char[]>(1024);  // 智能指针管理的堆资源
        strcpy(pdata_smart.get(), "智能指针管理的内存");
        std::cout << "智能指针管理的内存内容: " << pdata_smart.get() << std::endl;
        
        // 可以通过移动语义转移所有权
        auto moved_smart = std::move(pdata_smart);
        std::cout << "移动后，新智能指针内容: " << moved_smart.get() << std::endl;
        std::cout << "原智能指针是否为空: " << (pdata_smart ? "否" : "是") << std::endl;
        
        // 离开作用域时，moved_smart会自动释放资源，无需手动delete
    }
    
    std::cout << "\n--- 4. RAII类管理堆资源 (XData) ---" << std::endl;
    {
        XData data;  // RAII类对象在栈上，但管理的资源在堆上
        strcpy(data.getData(), "RAII类管理的资源");
        std::cout << "XData对象管理的资源内容: " << data.getData() << std::endl;
        
        // 可以通过移动语义转移所有权
        XData moved_data = std::move(data);
        std::cout << "移动后，新XData对象资源内容: " << moved_data.getData() << std::endl;
        
        // 通过函数返回值获取RAII对象
        XData returned_data = createXData();
        std::cout << "从函数返回的XData内容: " << returned_data.getData() << std::endl;
    }
    
    // std::cout << "\n--- 5. IntArray类示例 (int数组RAII) ---" << std::endl;
    // {
    //     IntArray arr(5);
    //     for (size_t i = 0; i < arr.size(); ++i) {
    //         arr[i] = static_cast<int>(i * 100);
    //     }
        
    //     std::cout << "IntArray内容: ";
    //     for (size_t i = 0; i < arr.size(); ++i) {
    //         std::cout << arr[i] << " ";
    //     }
    //     std::cout << std::endl;
        
    //     // 移动语义转移所有权
    //     IntArray moved_arr = std::move(arr);
    //     std::cout << "移动后的IntArray大小: " << moved_arr.size() << std::endl;
        
    //     // 从函数获取IntArray
    //     IntArray returned_arr = createIntArray(3);
    //     std::cout << "从函数返回的IntArray内容: ";
    //     for (size_t i = 0; i < returned_arr.size(); ++i) {
    //         std::cout << returned_arr[i] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return 0;
}