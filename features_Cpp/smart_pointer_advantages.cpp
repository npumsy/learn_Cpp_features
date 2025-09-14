#include <iostream>
#include <memory>
#include <stdexcept>

// 示例类
class Demo {
public:
    Demo(int v) : value(v) {
        std::cout << "Demo(" << value << ") constructed\n";
    }
    ~Demo() {
        std::cout << "Demo(" << value << ") destroyed\n";
    }
    void show() const {
        std::cout << "Value: " << value << '\n';
    }
private:
    int value;
};

// 手动管理内存
void processDataRaw(Demo* data) {
    std::cout << "[Using raw pointer] ";
    data->show();
}
void rawStackData(){
    // 直接用栈对象（Data obj;）确实是首选，
    Demo stackData(42);
    processDataRaw(&stackData);
    // 自动调用 ~Demo()，无需手动管理
}
void rawPointer(){
    // 为什么有时候要用智能指针管理对象，而不是直接用栈对象（即 Data obj;）？
    // 但当对象的生命周期、所有权或性能需求超出栈对象的能力时，我们就需要指针来管理堆上的对象。
    {
        Demo* rawData = new Data(42);
        processDataRaw(rawData);
        // ❌ 如果忘了 delete rawData，会造成内存泄漏
        // ❌ 如果在中间抛出异常，delete 也不会执行
        delete rawData; // 手动释放，容易忘记或重复释放
    }
    std::cout << "Raw pointer block ends.\n";
}

/// 1️⃣ 自动内存管理，避免泄漏
void automaticMemoryManagement() {
    std::cout << "\n[1️⃣ 自动内存管理示例]\n";
    std::unique_ptr<Demo> ptr = std::make_unique<Demo>(10);
    ptr->show();
    // 离开作用域后，自动释放内存
}

/// 2️⃣ 明确所有权语义（独占 vs 共享）
void ownershipSemantics() {
    std::cout << "\n[2️⃣ 所有权语义示例]\n";

    // 独占所有权
    std::unique_ptr<Demo> uptr = std::make_unique<Demo>(20);
    // std::unique_ptr<Demo> uptr2 = uptr; // ❌ 编译错误：不能复制 unique_ptr
    std::unique_ptr<Demo> uptr2 = std::move(uptr); // ✅ 转移所有权
    if (!uptr) std::cout << "uptr 已失去所有权\n";

    // 共享所有权
    std::shared_ptr<Demo> sptr1 = std::make_shared<Demo>(30);
    std::shared_ptr<Demo> sptr2 = sptr1;
    std::cout << "共享引用计数: " << sptr1.use_count() << '\n';
}

/// 3️⃣ 安全的所有权转移
std::unique_ptr<Demo> makeDemo() {
    std::unique_ptr<Demo> ptr = std::make_unique<Demo>(40);
    return ptr; // 返回时转移所有权（移动语义）
}

void transferOwnership() {
    std::cout << "\n[3️⃣ 所有权转移示例]\n";
    std::unique_ptr<Demo> ptr = makeDemo();
    ptr->show();
}

/// 4️⃣ 自动引用计数（shared_ptr）
void referenceCounting() {
    std::cout << "\n[4️⃣ 自动引用计数示例]\n";
    std::shared_ptr<Demo> sp1 = std::make_shared<Demo>(50);
    std::cout << "引用计数: " << sp1.use_count() << '\n';

    {
        std::shared_ptr<Demo> sp2 = sp1;
        std::cout << "引用计数 after copy: " << sp1.use_count() << '\n';
    } // sp2 离开作用域
    std::cout << "引用计数 after sp2 out of scope: " << sp1.use_count() << '\n';
}

/// 5️⃣ 异常安全
void mayThrow(bool shouldThrow) {
    std::unique_ptr<Demo> ptr = std::make_unique<Demo>(60);
    if (shouldThrow) throw std::runtime_error("发生异常！");
}

void exceptionSafety() {
    std::cout << "\n[5️⃣ 异常安全示例]\n";
    try {
        mayThrow(true);
    } catch (const std::exception& e) {
        std::cout << "捕获异常: " << e.what() << '\n';
    }
    // 即使异常发生，ptr 也已正确释放资源
}

/// 主函数依次调用各示例
int main() {
    automaticMemoryManagement();
    ownershipSemantics();
    transferOwnership();
    referenceCounting();
    exceptionSafety();
    return 0;
}
