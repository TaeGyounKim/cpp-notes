#include <iomanip>
#include <iostream>

int main()
{
    int number{ 42 };
    double value{ 1.36587 };

    // {:7}      -> std::setw(7)
    std::cout << '|' << std::setw(7) << number << "|\n";

    // {:_<7}    -> std::left, std::setfill('_')
    std::cout << '|' << std::left << std::setfill('_') << std::setw(7)
              << number << "|\n";
    std::cout << std::right << std::setfill(' ');   // 설정을 되돌린다.

    // {:x}, {:#x} -> std::hex, std::showbase
    std::cout << std::hex << number << ' ' << std::showbase << number
              << '\n';
    std::cout << std::dec << std::noshowbase;

    // {:.2f}    -> std::fixed, std::setprecision(2)
    std::cout << std::fixed << std::setprecision(2) << value << '\n';

    // {:06d}    -> std::setfill('0'), std::setw(6)
    std::cout << std::setfill('0') << std::setw(6) << number << '\n';
}
