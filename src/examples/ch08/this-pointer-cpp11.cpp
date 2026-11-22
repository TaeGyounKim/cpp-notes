#include <iostream>

class Reading
{
public:
    void set(double celsius)
    {
        this->celsius = celsius;   // this는 C++98부터 있다.
    }
    double get() const { return celsius; }

private:
    double celsius{ 0.0 };
};

int main()
{
    Reading reading;
    reading.set(25.0);
    std::cout << reading.get() << '\n';
}
