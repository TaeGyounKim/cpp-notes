#include <functional>
#include <iostream>
#include <memory>
#include <string>

// 제네릭 람다·캡처 표현식(C++14), 템플릿 람다(C++20), 재귀 람다(C++23),
// invoke(C++17)가 없다. 반환은 std::function, 재귀는 std::function이 자신을
// 참조로 캡처하는 방식, 이동 캡처는 shared_ptr로 대신한다.
std::function<double(double)> makeScaler(double factor)
{
    return [factor](double x) { return x * factor; };
}

int main()
{
    auto label = std::make_shared<std::string>("온도");
    auto show = [label](int v) { std::cout << *label << ' ' << v << '\n'; };
    show(23);

    std::function<int(int)> fib;
    fib = [&fib](int n) { return n < 2 ? n : fib(n - 1) + fib(n - 2); };

    auto scale = makeScaler(1.8);
    std::cout << scale(25.0) << ' ' << fib(9) << '\n';
}
