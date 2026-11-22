#include <iostream>
#include <string>

// 함수 호출·역참조 연산자 오버로딩은 C++98부터 있다.
// static operator()(C++23)가 없으므로 보통 멤버로 쓴다.
class Above
{
public:
    explicit Above(double limit) : m_limit(limit) {}
    bool operator()(double value) const { return value > m_limit; }

private:
    double m_limit;
};

template <typename T>
class Owner
{
public:
    explicit Owner(T* ptr) : m_ptr(ptr) {}
    ~Owner() { delete m_ptr; }
    Owner(const Owner&) = delete;              // = delete는 C++11
    Owner& operator=(const Owner&) = delete;
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }

private:
    T* m_ptr;
};

int main()
{
    Above hot(25.0);
    Owner<std::string> s(new std::string("센서"));
    s->append("-7");
    std::cout << std::boolalpha << hot(26.0) << ' ' << *s << '\n';
}
