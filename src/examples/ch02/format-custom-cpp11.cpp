#include <iostream>
#include <vector>

struct Color
{
    int red;
    int green;
    int blue;
};

// std::formatter 대신: 스트림에 출력하는 << 연산자를 만든다.
std::ostream& operator<<(std::ostream& out, const Color& color)
{
    out << "rgb(" << color.red << ", " << color.green << ", " << color.blue
        << ')';
    return out;
}

int main()
{
    Color orange{ 255, 128, 0 };
    std::cout << orange << '\n';

    // 범위 출력 대신: 반복문으로 원소를 하나씩 출력한다.
    std::vector<int> values{ 11, 22, 33 };
    std::cout << '[';
    for (std::size_t i{ 0 }; i < values.size(); ++i) {
        if (i != 0) {
            std::cout << ", ";
        }
        std::cout << values[i];
    }
    std::cout << "]\n";
}
