#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Tracer
{
public:
    explicit Tracer(const std::string& name) : m_name(name) {}
    ~Tracer() { std::cout << "  " << m_name << " 정리\n"; }

private:
    std::string m_name;
};

void inner() { throw std::invalid_argument("inner에서 던짐"); }

// std::make_unique는 C++14. C++11에서는 unique_ptr 생성자에 new를 넘긴다.
void middle()
{
    Tracer onStack("지역 객체");
    std::unique_ptr<Tracer> owned(new Tracer("unique_ptr"));
    try {
        inner();
    } catch (...) {
        std::cout << "  middle: 정리할 것을 정리하고 다시 던짐\n";
        throw;   // throw;는 C++98부터 있다.
    }
}

int main()
{
    try {
        middle();
    } catch (const std::invalid_argument& e) {
        std::cout << "main: " << e.what() << '\n';
    }
}
