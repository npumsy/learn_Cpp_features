#include <iostream>
#include <memory>
#include <string>

// 前向声明两个类，因为它们互相引用
class Person;
class Car;

// Person类，拥有Car的shared_ptr
class Person {
private:
    std::string name_;
    // 使用shared_ptr指向Car（强引用）
    std::shared_ptr<Car> car_;

public:
    Person(const std::string& name) : name_(name) {
        std::cout << "Person构造函数: " << name_ << std::endl;
    }

    ~Person() {
        std::cout << "Person析构函数: " << name_ << std::endl;
    }

    void set_car(std::shared_ptr<Car> car) {
        car_ = car;
    }

    // 获取关联的Car
    std::shared_ptr<Car> get_car() {
        return car_;
    }

    const std::string& get_name() const {
        return name_;
    }
};

// Car类，如果使用shared_ptr指向Person会导致循环引用
class Car {
private:
    std::string brand_;
    // 使用weak_ptr指向Person（弱引用，不会增加引用计数）
    std::weak_ptr<Person> owner_;

public:
    Car(const std::string& brand) : brand_(brand) {
        std::cout << "Car构造函数: " << brand_ << std::endl;
    }

    ~Car() {
        std::cout << "Car析构函数: " << brand_ << std::endl;
    }

    void set_owner(std::shared_ptr<Person> owner) {
        owner_ = owner;
    }

    // 安全地访问owner
    void display_owner() {
        // 尝试将weak_ptr转换为shared_ptr
        if (auto owner = owner_.lock()) {
            std::cout << brand_ << "的车主是: " << owner->get_name() << std::endl;
        } else {
            std::cout << brand_ << "没有车主" << std::endl;
        }
    }

    // 检查车主是否还存在
    bool has_owner() const {
        return !owner_.expired();
    }

    const std::string& get_brand() const {
        return brand_;
    }
};

// 演示循环引用问题的函数
void demonstrate_cycle_reference() {
    std::cout << "\n===== 演示循环引用问题 =====" << std::endl;
    std::cout << "// 注意：在这个简化示例中，我们将展示如果Car也使用shared_ptr指向Person会发生什么" << std::endl;

    // 创建两个对象，它们互相引用
    {  // 新的作用域
        auto alice = std::make_shared<Person>("Alice");
        auto bmw = std::make_shared<Car>("BMW");

        // 设置相互引用
        alice->set_car(bmw);
        // 如果Car类也使用shared_ptr<Person>，这里会形成循环引用
        // bmw->set_owner(alice); // 注意：在我们的实现中Car使用的是weak_ptr，所以不会形成循环引用

        std::cout << "\n离开内部作用域..." << std::endl;
    }
    std::cout << "\n成功离开了作用域，Person和Car都被正确析构，没有内存泄漏！" << std::endl;
    std::cout << "（因为我们在Car中使用了weak_ptr来避免循环引用）" << std::endl;
}

// 演示weak_ptr的基本用法
void demonstrate_weak_ptr_basics() {
    std::cout << "\n===== 演示weak_ptr的基本用法 =====" << std::endl;
    
    // 创建一个shared_ptr
    auto shared_ptr = std::make_shared<int>(42);
    
    // 创建一个weak_ptr指向同一个对象
    std::weak_ptr<int> weak_ptr = shared_ptr;
    
    // 检查weak_ptr是否有效
    if (!weak_ptr.expired()) {
        std::cout << "weak_ptr有效，可以转换为shared_ptr" << std::endl;
        
        // 转换为shared_ptr并使用
        if (auto temp_ptr = weak_ptr.lock()) {
            std::cout << "通过转换后的shared_ptr访问值: " << *temp_ptr << std::endl;
            // temp_ptr离开作用域后，引用计数减1
        }
        
        // 获取引用计数
        std::cout << "shared_ptr的引用计数: " << shared_ptr.use_count() << std::endl;
    }
    
    // 重置shared_ptr，释放资源
    shared_ptr.reset();
    
    // 再次检查weak_ptr是否有效
    if (weak_ptr.expired()) {
        std::cout << "shared_ptr被释放后，weak_ptr已失效" << std::endl;
        
        // 尝试转换为shared_ptr，会得到空指针
        if (auto temp_ptr = weak_ptr.lock()) {
            std::cout << "这行代码不会执行" << std::endl;
        } else {
            std::cout << "无法从失效的weak_ptr获取shared_ptr" << std::endl;
        }
    }
}

// 演示weak_ptr在观察者模式中的应用
void demonstrate_weak_ptr_observer() {
    std::cout << "\n===== 演示weak_ptr在观察者模式中的应用 =====" << std::endl;
    
    // 创建Person和Car对象
    auto tom = std::make_shared<Person>("Tom");
    auto toyota = std::make_shared<Car>("Toyota");
    
    // 设置关联
    tom->set_car(toyota);
    toyota->set_owner(tom);
    
    // 显示关联信息
    std::cout << "\n初始关联状态: " << std::endl;
    toyota->display_owner();
    
    // 模拟Tom放弃了他的车
    tom->set_car(nullptr);
    
    std::cout << "\nTom放弃车后的状态: " << std::endl;
    std::cout << "- Tom的车: " << (tom->get_car() ? tom->get_car()->get_brand() : "无") << std::endl;
    
    // 即使Tom没有车了，Car仍然知道它的主人
    toyota->display_owner();
    
    // 现在模拟Tom被销毁
    std::cout << "\n销毁Tom对象..." << std::endl;
    tom.reset();
    
    // Car检测主人是否还存在
    std::cout << "\nTom销毁后的状态: " << std::endl;
    std::cout << "- Toyota是否有车主: " << (toyota->has_owner() ? "是" : "否") << std::endl;
    toyota->display_owner();
}

int main() {
    std::cout << "===== weak_ptr智能指针示例（初学者版）=====" << std::endl;
    std::cout << "// weak_ptr是一种弱引用智能指针，不会增加引用计数" << std::endl;
    std::cout << "// 主要用途：1. 解决shared_ptr的循环引用问题" << std::endl;
    std::cout << "//         2. 观察对象是否存在而不延长其生命周期" << std::endl;
    
    // 演示基本用法
    demonstrate_weak_ptr_basics();
    
    // 演示循环引用问题的解决
    demonstrate_cycle_reference();
    
    // 演示在实际场景中的应用
    demonstrate_weak_ptr_observer();
    
    std::cout << "\n===== weak_ptr智能指针示例结束 =====" << std::endl;
    std::cout << "\n初学者注意事项:\n";
    std::cout << "1. weak_ptr不能直接使用，需要先转换为shared_ptr" << std::endl;
    std::cout << "2. 使用lock()方法安全地转换，转换失败会返回空指针" << std::endl;
    std::cout << "3. 使用expired()方法检查对象是否已被销毁" << std::endl;
    std::cout << "4. 当两个对象互相引用时，让其中一个使用weak_ptr避免循环引用" << std::endl;
    std::cout << "5. weak_ptr特别适合观察者模式和缓存场景" << std::endl;
    
    return 0;
}