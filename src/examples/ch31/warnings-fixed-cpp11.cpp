#include <cstdio>
#include <vector>

// 경고를 모두 고친 판. -Werror를 줘도 컴파일된다.
int count_large(const std::vector<int>& values, int limit)
{
    int count = 0;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (values[i] > limit) {
            ++count;
        }
    }
    return count;
}

int sign_of(int x)
{
    if (x > 0) { return 1; }
    if (x < 0) { return -1; }
    return 0;
}

int main()
{
    std::vector<int> v;
    v.push_back(3);
    v.push_back(8);
    v.push_back(1);
    v.push_back(9);
    std::printf("count: %d\n", count_large(v, 5));
    std::printf("sign: %d %d %d\n", sign_of(7), sign_of(0), sign_of(-2));
}
