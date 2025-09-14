#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

// 1. 基本函数对象类
class Adder {
private:
    int value_; // 成员变量作为函数对象的状态

public:
    // 构造函数，初始化状态
    explicit Adder(int value) : value_(value) {
        std::cout << "Adder构造函数被调用，值为: " << value_ << std::endl;
    }

    // 重载operator()，使对象可以像函数一样被调用
    int operator()(int x) const {
        std::cout << "Adder调用: " << x << " + " << value_ << " = " << (x + value_) << std::endl;
        return x + value_;
    }
};
// class Adder {
// private:
//     int value_; // 成员变量作为函数对象的状态
// public:
//     // 构造函数
//     explicit Adder(int value) : value_(value) {}
//     // 重载operator()，使对象可以像函数一样被调用
//     int operator()(int x) const {  return x + value_;   }
// };

// 2. 用于排序的函数对象
class Person {
public:
    std::string name_;
    int age_;

    Person(const std::string& name, int age) : name_(name), age_(age) {}
};

// 按年龄排序的函数对象
class SortByAge {
public:
    bool operator()(const Person& p1, const Person& p2) const {
        return p1.age_ < p2.age_;
    }
};

// 按名字排序的函数对象
class SortByName {
public:
    bool operator()(const Person& p1, const Person& p2) const {
        return p1.name_ < p2.name_;
    }
};

// 3. 用于统计的函数对象（带状态）
class Counter {
private:
    int count_;
    int threshold_;

public:
    Counter(int threshold = 0) : count_(0), threshold_(threshold) {}

    // 统计大于阈值的元素个数
    void operator()(int value) {
        if (value > threshold_) {
            ++count_;
            std::cout << value << " 大于 " << threshold_ << "，计数增加到: " << count_ << std::endl;
        }
    }

    // 获取统计结果
    int get_count() const {
        return count_;
    }
};

// 4. 函数对象作为返回类型
class OperationFactory {
public:
    enum OperationType {
        ADD, SUBTRACT, MULTIPLY, DIVIDE
    };

    // 返回一个函数对象
    static std::function<int(int, int)> get_operation(OperationType type) {
        switch (type) {
            case ADD:
                return [](int a, int b) { return a + b; };
            case SUBTRACT:
                return [](int a, int b) { return a - b; };
            case MULTIPLY:
                return [](int a, int b) { return a * b; };
            case DIVIDE:
                return [](int a, int b) { return b != 0 ? a / b : 0; };
            default:
                return [](int, int) { return 0; };
        }
    }
};

// 5. 函数对象与标准库算法结合
class Printer {
public:
    template<typename T>
    void operator()(const T& value) const {
        std::cout << value << " ";
    }
};

// 6. 带有引用捕获的lambda表达式（作为函数对象的现代替代）
void demonstrate_lambda() {
    std::cout << "\n6. Lambda表达式（现代函数对象）:" << std::endl;
    
    // 基本lambda
    auto square = [](int x) { return x * x; };
    std::cout << "5的平方: " << square(5) << std::endl;
    
    // 捕获外部变量
    int factor = 2;
    auto multiply = [factor](int x) { return x * factor; };
    std::cout << "5乘以" << factor << ": " << multiply(5) << std::endl;
    
    // 引用捕获（可以修改外部变量）
    auto incrementer = [&factor]() { ++factor; };
    incrementer();
    std::cout << "factor增加后: " << factor << std::endl;
    std::cout << "5乘以新的factor值: " << multiply(5) << std::endl;
    
    // 捕获所有外部变量
    auto print_all = [&]() {
        std::cout << "factor = " << factor << std::endl;
    };
    print_all();
}

int main() {
    std::cout << "===== 函数对象（Functor）示例 =====" << std::endl;

    // 1. 基本函数对象使用
    std::cout << "\n1. 基本函数对象使用:" << std::endl;
    Adder add5(5); // 创建函数对象，初始化为加5
    Adder add10(10); // 创建另一个函数对象，初始化为加10
    
    std::cout << "10 + 5 = " << add5(10) << std::endl;
    std::cout << "10 + 10 = " << add10(10) << std::endl;
    
    // 2. 函数对象作为参数传递
    std::cout << "\n2. 函数对象作为参数传递:" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> results;
    results.resize(numbers.size());
    
    // 使用std::transform和函数对象
    std::transform(numbers.begin(), numbers.end(), results.begin(), add5);
    
    std::cout << "转换后的数组: ";
    for (int n : results) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 3. 用于排序的函数对象
    std::cout << "\n3. 用于排序的函数对象:" << std::endl;
    std::vector<Person> people = {{
        Person("张三", 25),
        Person("李四", 30),
        Person("王五", 22),
        Person("赵六", 35)
    }};
    
    // 按年龄排序
    std::sort(people.begin(), people.end(), SortByAge());
    std::cout << "按年龄排序: " << std::endl;
    for (const auto& person : people) {
        std::cout << person.name_ << " (" << person.age_ << ")" << std::endl;
    }
    
    // 按名字排序
    std::sort(people.begin(), people.end(), SortByName());
    std::cout << "按名字排序: " << std::endl;
    for (const auto& person : people) {
        std::cout << person.name_ << " (" << person.age_ << ")" << std::endl;
    }
    
    // 4. 带有状态的函数对象
    std::cout << "\n4. 带有状态的函数对象:" << std::endl;
    Counter count_gt3(3); // 统计大于3的元素
    for (int n : numbers) {
        count_gt3(n); // 调用函数对象，更新状态
    }
    std::cout << "大于3的元素个数: " << count_gt3.get_count() << std::endl;
    
    // 5. 从工厂获取函数对象
    std::cout << "\n5. 从工厂获取函数对象:" << std::endl;
    auto add_operation = OperationFactory::get_operation(OperationFactory::ADD);
    auto multiply_operation = OperationFactory::get_operation(OperationFactory::MULTIPLY);
    
    std::cout << "3 + 4 = " << add_operation(3, 4) << std::endl;
    std::cout << "3 * 4 = " << multiply_operation(3, 4) << std::endl;
    
    // 6. Lambda表达式（现代函数对象）
    demonstrate_lambda();
    
    // 7. 函数对象与标准库算法结合的更多例子
    std::cout << "\n7. 函数对象与标准库算法结合的更多例子:" << std::endl;
    std::vector<std::string> words = {"apple", "banana", "cherry", "date"};
    
    std::cout << "使用Printer函数对象打印: ";
    std::for_each(words.begin(), words.end(), Printer());
    std::cout << std::endl;
    
    // 使用lambda表达式（现代方式）
    std::cout << "使用lambda表达式打印: ";
    std::for_each(words.begin(), words.end(), [](const std::string& word) {
        std::cout << word << " ";
    });
    std::cout << std::endl;
    
    // 8. 函数对象的优势总结
    std::cout << "\n8. 函数对象的优势总结:" << std::endl;
    std::cout << "- 可以保持状态（通过成员变量）" << std::endl;
    std::cout << "- 可以内联，比函数指针更高效" << std::endl;
    std::cout << "- 可以特化和重载" << std::endl;
    std::cout << "- 与STL算法良好集成" << std::endl;
    std::cout << "- C++11的lambda表达式提供了更简洁的语法" << std::endl;
    
    std::cout << "\n===== 函数对象（Functor）示例结束 =====" << std::endl;
    
    return 0;
}