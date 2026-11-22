#include <algorithm>
#include <cstddef>
#include <cstring>
#include <optional>
#include <print>
#include <utility>
#include <vector>

// 함수 템플릿: 배열에서 값을 찾아 인덱스를 돌려준다.
template <typename T>
std::optional<std::size_t> indexOf(const T& value, const T* arr,
                                   std::size_t size)
{
    for (std::size_t i{ 0 }; i < size; ++i) {
        if (arr[i] == value) { return i; }
    }
    return {};
}

// 크기를 컴파일러가 아는 배열용. 타입이 아닌 매개변수 N
template <typename T, std::size_t N>
std::optional<std::size_t> indexOf(const T& value, const T (&arr)[N])
{
    return indexOf(value, arr, N);
}

// 템플릿이 아닌 오버로드: C 문자열은 내용을 비교한다.
std::optional<std::size_t> indexOf(const char* value, const char** arr,
                                   std::size_t size)
{
    for (std::size_t i{ 0 }; i < size; ++i) {
        if (std::strcmp(arr[i], value) == 0) { return i; }
    }
    return {};
}

void show(std::optional<std::size_t> r)
{
    if (r) { std::println("{}", *r); } else { std::println("없음"); }
}

// 함수 템플릿을 클래스 템플릿의 friend로
template <typename T> class Bin;
template <typename T> Bin<T> operator+(const Bin<T>& a, const Bin<T>& b);

template <typename T>
class Bin
{
public:
    explicit Bin(std::vector<T> items) : m_items{ std::move(items) } {}
    // 같은 T로 인스턴스화한 operator+만 friend
    friend Bin operator+ <T>(const Bin& a, const Bin& b);
    void print() const { std::println("{}", m_items); }

private:
    std::vector<T> m_items;
};

template <typename T>
Bin<T> operator+(const Bin<T>& a, const Bin<T>& b)
{
    std::size_t n{ std::min(a.m_items.size(), b.m_items.size()) };
    std::vector<T> sum(n);
    for (std::size_t i{ 0 }; i < n; ++i) {
        sum[i] = a.m_items[i] + b.m_items[i];   // private 멤버에 접근
    }
    return Bin<T>{ sum };
}

int main()
{
    int ids[]{ 10, 20, 30, 40 };
    show(indexOf(30, ids, 4));            // T를 int로 추론
    show(indexOf<int>(30, ids, 4));       // T를 직접 지정
    show(indexOf(25, ids));               // 크기 N을 배열에서 추론

    double ratios[]{ 0.5, 1.0, 2.5 };
    // indexOf(1, ratios, 3);             // 오류: T가 int인가 double인가?
    show(indexOf<double>(1, ratios, 3));  // T를 정하면 1이 1.0으로 바뀐다.

    const char word[]{ "습도" };          // 리터럴과 다른 주소의 배열
    const char* names[]{ "온도", "습도", "기압" };
    show(indexOf(word, names, 3));                // 템플릿이 아닌 판: 1
    show(indexOf<const char*>(word, names, 3));   // 템플릿: 포인터만 비교

    Bin<int> a{ { 1, 2, 3 } };
    Bin<int> b{ { 10, 20 } };
    (a + b).print();
}
