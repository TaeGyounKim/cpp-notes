#include <cstdarg>
#include <cstdio>
#include <initializer_list>

// C 스타일 가변 인자는 C++98부터 그대로 쓸 수 있다.
int sumInts(int count, ...)
{
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; ++i) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

// C++11의 더 안전한 대안: 초기화 리스트는 개수와 타입을 안다.
int sumList(std::initializer_list<int> values)
{
    int total = 0;
    for (int v : values) { total += v; }
    return total;
}

int main()
{
    std::printf("%d %d\n", sumInts(3, 1, 2, 3), sumList({ 1, 2, 3 }));
}
