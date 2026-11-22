#include <print>

int main()
{
    // 배열의 크기를 실행 중에 정할 수 있다.
    int size{ 4 };
    int* numbers{ new int[size]{} };   // int 네 칸, 모두 0

    // 보통의 배열처럼 번호로 쓴다.
    numbers[0] = 10;
    numbers[3] = 40;

    for (int i{ 0 }; i < size; ++i) {
        std::println("numbers[{}] = {}", i, numbers[i]);
    }

    // new[]로 만든 것은 delete[]로 돌려준다.
    delete[] numbers;
    numbers = nullptr;
}
