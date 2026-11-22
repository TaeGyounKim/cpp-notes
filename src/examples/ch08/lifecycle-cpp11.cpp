#include <iostream>

class Temperature
{
public:
    explicit Temperature(double celsius) : m_celsius(celsius) {}
    ~Temperature() { std::cout << "소멸: " << m_celsius << '\n'; }

    Temperature(const Temperature& src) = default;
    Temperature& operator=(const Temperature& rhs)
    {
        if (this != &rhs) {
            m_celsius = rhs.m_celsius;
        }
        return *this;
    }

    double getCelsius() const { return m_celsius; }

private:
    double m_celsius;
};

int main()
{
    Temperature a(10.0);
    Temperature b(20.0);
    a = b;
    std::cout << "a: " << a.getCelsius() << '\n';
}
