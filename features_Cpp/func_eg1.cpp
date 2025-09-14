#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>
struct Functor {
    void operator()(const std::string& str) const {
        std::cout << "Functor调用: " << str << std::endl;
    }
};
int main() {
    std::cout << "===== 函数对象（Functor）示例 =====" << std::endl;
}