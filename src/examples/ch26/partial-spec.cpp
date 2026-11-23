#include <cstddef>
#include <cstring>
#include <memory>
#include <optional>
#include <print>
#include <string>
#include <utility>
#include <vector>

// 기본 템플릿: 크기가 템플릿 인수인 고정 크기 표
template <typename T, std::size_t R, std::size_t C>
class Fixed {
public:
    T& at(std::size_t r, std::size_t c) { return m_cells[r][c]; }
    static constexpr const char* kind{ "기본" };
private:
    T m_cells[R][C]{};
};

// 부분 특수화 1: T만 const char*로 정하고 R, C는 그대로 매개변수
template <std::size_t R, std::size_t C>
class Fixed<const char*, R, C> {
public:
    std::string& at(std::size_t r, std::size_t c) { return m_cells[r][c]; }
    static constexpr const char* kind{ "const char* 특수화" };
private:
    std::string m_cells[R][C];   // 문자열을 복사해 소유한다.
};

// 기본 템플릿: 값을 담는 상자들
template <typename T>
class Boxes {
public:
    explicit Boxes(std::size_t n) : m_items(n) {}
    T& at(std::size_t i) { return m_items[i]; }
private:
    std::vector<T> m_items;
};

// 부분 특수화 2: "모든 포인터 타입". Boxes<int*>이면 U는 int
template <typename U>
class Boxes<U*> {
public:
    explicit Boxes(std::size_t n) : m_items(n) {}
    Boxes(const Boxes& src) : m_items(src.m_items.size())   // 깊은 복사
    {
        for (std::size_t i{ 0 }; i < m_items.size(); ++i) {
            if (src.m_items[i]) {
                m_items[i] = std::make_unique<U>(*src.m_items[i]);
            }
        }
    }
    Boxes& operator=(const Boxes& rhs)                      // 복사 후 교환
    {
        Boxes copy{ rhs };
        m_items.swap(copy.m_items);
        return *this;
    }
    Boxes(Boxes&&) noexcept = default;
    Boxes& operator=(Boxes&&) noexcept = default;
    std::unique_ptr<U>& at(std::size_t i) { return m_items[i]; }
private:
    std::vector<std::unique_ptr<U>> m_items;   // 가리키는 객체를 소유
};

// 함수 템플릿은 부분 특수화가 안 된다.
// 대신 더 구체적인 함수 템플릿으로 "오버로딩"한다.
template <typename T>
std::optional<std::size_t> index_of(const T& v, const T* arr, std::size_t n)
{
    for (std::size_t i{ 0 }; i < n; ++i) { if (arr[i] == v) { return i; } }
    return std::nullopt;
}
template <typename T>   // 포인터용: 가리키는 값끼리 비교
std::optional<std::size_t> index_of(T* v, T* const* arr, std::size_t n)
{
    for (std::size_t i{ 0 }; i < n; ++i) { if (*arr[i] == *v) { return i; } }
    return std::nullopt;
}
// 템플릿이 아닌 오버로드: 똑같이 구체적이면 이쪽이 이긴다.
std::optional<std::size_t> index_of(const char* v, const char* const* arr,
                                    std::size_t n)
{
    for (std::size_t i{ 0 }; i < n; ++i) {
        if (std::strcmp(arr[i], v) == 0) { return i; }
    }
    return std::nullopt;
}

int main()
{
    Fixed<int, 2, 2> nums;
    Fixed<const char*, 2, 2> words;
    nums.at(1, 1) = 7;
    words.at(0, 1) = "hello";
    std::println("{}: {} / {}: {}", nums.kind, nums.at(1, 1), words.kind,
                 words.at(0, 1));
    // Fixed<2, 2> bad;   // 오류: 인수는 여전히 셋

    Boxes<int*> a{ 2 };
    a.at(0) = std::make_unique<int>(10);
    Boxes<int*> b{ a };                       // 깊은 복사
    *b.at(0) = 20;
    std::println("a {} / b {}", *a.at(0), *b.at(0));

    int x{ 3 }, y{ 3 }, z{ 5 };
    int values[]{ 1, 2, 3 };
    int* ptrs[]{ &z, &y };
    const char* names[]{ "kim", "lee" };
    std::string who{ "lee" };
    std::println("{} {} {}", index_of(x, values, 3).value_or(99),
                 index_of(&x, ptrs, 2).value_or(99),          // 값 3을 찾음
                 index_of(who.c_str(), names, 2).value_or(99));
}
