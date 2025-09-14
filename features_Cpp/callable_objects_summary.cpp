#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

// ===== 1. Functor（函数对象类）=====
// 重载了operator()的类的实例，可以像函数一样被调用，且可以保持状态
class Adder {
private:
    int increment_; // 可以保持状态

public:
    explicit Adder(int inc) : increment_(inc) {}
    
    // 重载operator()，使对象可以像函数一样被调用
    int operator()(int x) const {
        return x + increment_;
    }
};

// 用于排序的函数对象
class SortByLength {
public:
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};

// ===== 2. Lambda表达式 =====
// C++11引入的匿名函数对象，提供了简洁的语法
//lambda 表达式： [ capture-list ] ( params ) -> ret { body }
// capture-list: 它使这个匿名函数可以访问外部（父作用域）变量，在类中就是添加this，
//               捕捉方式有按值和按引用两种。比如[a, &b]表示按值捕捉a，
//               按引用捕捉b；[&, a]表示按引用捕捉所有父作用域变量，除了a按值捕捉，
//               [=，&b]表示按值捕捉所有父作用域变量，除了b按引用捕捉。
// params： 表达式传递的参数
// ret：返回结果
void demonstrate_lambda() {
    std::cout << "\n===== Lambda表达式（核心用法）=====" << std::endl;
    
    // 基本lambda：[捕获列表](参数列表) -> 返回类型 {函数体}
    auto square = [](int x) { return x * x; };
    std::cout << "5的平方: " << square(5) << std::endl;
    
    // 捕获外部变量（按值）
    int factor = 2;
    auto multiply = [factor](int x) { return x * factor; };
    std::cout << "5乘以" << factor << ": " << multiply(5) << std::endl;
    
    // 捕获外部变量（按引用）
    auto incrementer = [&factor]() { ++factor; };
    incrementer();
    std::cout << "factor增加后: " << factor << std::endl;
    
    // 捕获所有外部变量（按值）
    auto print_all = [=]() {
        std::cout << "按值捕获的factor = " << factor << std::endl;
    };
    
    // 捕获所有外部变量（按引用）
    auto modify_all = [&]() {
        factor = 10; // 修改外部变量
        std::cout << "按引用捕获并修改factor为: " << factor << std::endl;
    };
    
    print_all();
    modify_all();
    
    // Lambda在STL算法中的应用
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "原数组: ";
    for (int n : numbers) { std::cout << n << " "; }
    std::cout << std::endl;
    
    // 使用lambda作为谓词
    std::cout << "大于2的元素: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n > 2) std::cout << n << " ";
    });
    std::cout << std::endl;
    
    // 使用lambda转换数据
    std::transform(numbers.begin(), numbers.end(), numbers.begin(), 
                  [](int n) { return n * 2; });
    std::cout << "转换后数组（所有元素乘2）: ";
    for (int n : numbers) { std::cout << n << " "; }
    std::cout << std::endl;
}

// ===== 3. std::function 类模板 =====
// 通用多态函数包装器，可以存储任何可调用对象
void demonstrate_function() {
    std::cout << "\n===== std::function 类模板（核心用法）=====" << std::endl;
    
    // 存储函数指针
    auto add = [](int a, int b) { return a + b; };
    std::function<int(int, int)> f1 = add;
    std::cout << "函数指针: 3 + 4 = " << f1(3, 4) << std::endl;
    
    // 存储函数对象
    Adder add5(5);
    std::function<int(int)> f2 = add5;
    std::cout << "函数对象: 10 + 5 = " << f2(10) << std::endl;
    
    // 存储lambda表达式
    std::function<int(int)> f3 = [](int x) { return x * x; };
    std::cout << "Lambda: 6的平方 = " << f3(6) << std::endl;
    
    // 作为回调函数
    auto process_data = [](std::vector<int>& data, std::function<int(int)> processor) {
        for (auto& item : data) {
            item = processor(item);
        }
    };
    
    std::vector<int> values = {1, 2, 3, 4, 5};
    process_data(values, [](int x) { return x * 3; });
    
    std::cout << "应用回调后的数组: ";
    for (int v : values) { std::cout << v << " "; }
    std::cout << std::endl;
    
    // 作为返回类型
    auto create_operation = [](char op) -> std::function<int(int, int)> {
        switch (op) {
            case '+': return [](int a, int b) { return a + b; };
            case '-': return [](int a, int b) { return a - b; };
            case '*': return [](int a, int b) { return a * b; };
            default: return [](int, int) { return 0; };
        }
    };
    
    auto op = create_operation('*');
    std::cout << "创建的乘法操作: 5 * 6 = " << op(5, 6) << std::endl;
}

// ===== 4. std::bind 绑定器 =====
// 创建一个函数对象，将函数与其部分参数绑定
void demonstrate_bind() {
    std::cout << "\n===== std::bind 绑定器（核心用法）=====" << std::endl;
    
    // 绑定普通函数
    auto multiply = [](int a, int b) { return a * b; };
    
    // 绑定第一个参数为2
    auto double_it = std::bind(multiply, 2, std::placeholders::_1);
    std::cout << "绑定第一个参数为2: double_it(5) = " << double_it(5) << std::endl; // 2*5=10
    
    // 绑定第二个参数为3
    auto triple_it = std::bind(multiply, std::placeholders::_1, 3);
    std::cout << "绑定第二个参数为3: triple_it(5) = " << triple_it(5) << std::endl; // 5*3=15
    
    // 重新排序参数
    auto swap_args = std::bind(multiply, std::placeholders::_2, std::placeholders::_1);
    std::cout << "交换参数顺序: swap_args(2, 3) = " << swap_args(2, 3) << std::endl; // 3*2=6
    
    // 绑定成员函数
    class Calculator {
    public:
        int add(int a, int b) const { return a + b; }
        int subtract(int a, int b) const { return a - b; }
    };
    
    Calculator calc;
    auto add_with_10 = std::bind(&Calculator::add, &calc, 10, std::placeholders::_1);
    std::cout << "绑定成员函数: add_with_10(5) = " << add_with_10(5) << std::endl; // 10+5=15
    
    // 与STL算法结合
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "使用bind过滤大于2的元素: ";
    auto is_greater_than_2 = std::bind(std::greater<int>(), std::placeholders::_1, 2);
    std::for_each(numbers.begin(), numbers.end(), [&is_greater_than_2](int n) {
        if (is_greater_than_2(n)) {
            std::cout << n << " ";
        }
    });
    std::cout << std::endl;
}

// 总结4种可调用对象的适用场景
void summarize_callable_objects() {
    std::cout << "\n===== 4种可调用对象总结 =====" << std::endl;
    
    std::cout << "【Functor（函数对象类）】" << std::endl;
    std::cout << "- 适合需要保持状态的场景" << std::endl;
    std::cout << "- 可以通过继承和多态扩展" << std::endl;
    std::cout << "- 编译期解析，性能好" << std::endl;
    std::cout << "- 常用于自定义排序规则、算法谓词" << std::endl;
    
    std::cout << "\n【Lambda表达式】" << std::endl;
    std::cout << "- 语法简洁，定义和使用一体化" << std::endl;
    std::cout << "- 可以捕获外部变量" << std::endl;
    std::cout << "- 适合简短的一次性操作" << std::endl;
    std::cout << "- C++11及以上推荐使用，替代大部分函数对象" << std::endl;
    
    std::cout << "\n【std::function 类模板】" << std::endl;
    std::cout << "- 类型擦除，可存储任何可调用对象" << std::endl;
    std::cout << "- 适合需要类型统一的场景（如回调函数）" << std::endl;
    std::cout << "- 可以作为返回类型和参数传递" << std::endl;
    std::cout << "- 有一定的运行时开销" << std::endl;
    
    std::cout << "\n【std::bind 绑定器】" << std::endl;
    std::cout << "- 可以绑定部分参数，创建新的函数对象" << std::endl;
    std::cout << "- 可以重新排序函数参数" << std::endl;
    std::cout << "- 适合需要适配现有函数接口的场景" << std::endl;
    std::cout << "- C++11后部分功能可被lambda替代" << std::endl;
    
    std::cout << "\n【使用建议】" << std::endl;
    std::cout << "1. 简单的一次性操作优先使用lambda表达式" << std::endl;
    std::cout << "2. 需要保持复杂状态或复用的场景使用函数对象类" << std::endl;
    std::cout << "3. 需要类型统一的回调函数场景使用std::function" << std::endl;
    std::cout << "4. 复杂的参数绑定场景使用std::bind" << std::endl;
}

int main() {
    std::cout << "===== C++ 可调用对象（Callable Objects）核心用法总结 =====" << std::endl;
    
    // 演示各种可调用对象的核心用法
    demonstrate_lambda();
    demonstrate_function();
    demonstrate_bind();
    summarize_callable_objects();
    
    return 0;
}