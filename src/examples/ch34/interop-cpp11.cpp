#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// std::optional(C++17) 대신 bool + 출력 매개변수, println(C++23) 대신 cout.
// extern "C"와 unique_ptr 삭제자는 C++11에 그대로 있다.
extern "C" {
struct counter_t {
    int value;
};
counter_t* counter_new(void)
{
    return static_cast<counter_t*>(std::calloc(1, sizeof(counter_t)));
}
void counter_free(counter_t* c) { std::free(c); }
void counter_add(counter_t* c, int n) { c->value += n; }
int counter_get(const counter_t* c) { return c->value; }
}

class Counter final {
public:
    Counter() : m_handle(counter_new(), counter_free) {}
    void add(int n) { counter_add(m_handle.get(), n); }
    bool get(int& out) const
    {
        if (!m_handle) { return false; }
        out = counter_get(m_handle.get());
        return true;
    }

private:
    std::unique_ptr<counter_t, void (*)(counter_t*)> m_handle;
};

int main()
{
    Counter c;
    int n = 0;
    while (std::cin >> n) { c.add(n); }
    int total = 0;
    if (!c.get(total)) { return 1; }
    std::cout << "total " << total << '\n';
    return 0;
}
