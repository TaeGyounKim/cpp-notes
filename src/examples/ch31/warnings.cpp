#include <print>
#include <vector>

// 컴파일러 경고가 가리키는 버그들. 실행 전에 경고부터 읽어 보세요.
int count_large(const std::vector<int>& values, int limit)
{
    int count;                                    // 초기화하지 않음
    for (int i{ 0 }; i < values.size(); ++i) {    // signed/unsigned 비교
        int value{ values[i] };
        if (value = limit) {                      // >가 아니라 =
            ++count;
        }
    }
    return count;
}

int sign_of(int x)
{
    if (x > 0) { return 1; }
    if (x < 0) { return -1; }
}                                                 // 0이면 무엇을 돌려주나?

int main()
{
    std::vector<int> v{ 3, 8, 1, 9 };
    int unused{ 42 };
    std::println("5보다 큰 값의 개수: {}", count_large(v, 5));
    std::println("부호: {}", sign_of(7));
}
