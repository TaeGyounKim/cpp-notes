#include <cstddef>
#include <print>

int main()
{
    // 스택의 배열: 크기는 컴파일할 때 정해진 상수여야 한다.
    int a[5]{ 1, 2, 3, 4, 5 };
    int b[5]{ 1, 2 };   // 나머지는 0
    int c[5]{};         // 모두 0
    int d[]{ 7, 8, 9 }; // 크기를 초기화 목록에서 정한다(3).
    std::println("{} {} {} {}", a[4], b[4], c[0], sizeof(d) / sizeof(d[0]));

    // 자유 저장소의 배열: 크기를 실행할 때 정할 수 있다.
    std::size_t count{ 4 };
    int* scores{ new int[count]{ 90, 85 } };   // 나머지는 0
    for (std::size_t i{ 0 }; i < count; ++i) {
        std::print("{} ", scores[i]);
    }
    std::println("");
    delete[] scores;    // new[]에는 delete[]
    scores = nullptr;
}
