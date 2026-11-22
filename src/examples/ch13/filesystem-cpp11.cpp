#include <iostream>
#include <string>

// <filesystem>은 C++17. 그 전에는 Boost.Filesystem이나 운영체제 API를
// 썼고, 경로 문자열은 직접 나눴다.
int main()
{
    std::string p = "/data/sensors/room.csv";
    std::string::size_type slash = p.find_last_of('/');
    std::string parent = p.substr(0, slash);
    std::string file = p.substr(slash + 1);
    std::string::size_type dot = file.find_last_of('.');
    std::string stem = file.substr(0, dot);
    std::string ext = file.substr(dot);
    std::cout << parent << ' ' << file << ' ' << stem << ' ' << ext << '\n';
}
