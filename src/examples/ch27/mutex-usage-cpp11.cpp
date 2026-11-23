#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>

// osyncstream(C++20), 인라인 static 멤버(C++17)가 없으므로
// 문자열로 한 줄을 다 만든 뒤 뮤텍스로 보호해 한 번에 출력한다.
std::mutex g_out;
void say(const std::string& line)
{
    std::lock_guard<std::mutex> lock(g_out);
    std::cout << line;
}

std::timed_mutex g_slow;
void try_print(int id)
{
    std::unique_lock<std::timed_mutex> lock(g_slow,
                                            std::chrono::milliseconds(30));
    std::ostringstream os;
    os << "try " << id << (lock ? ": got it\n" : ": gave up\n");
    say(os.str());
    if (lock) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
}

int main()
{
    std::thread a(try_print, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::thread b(try_print, 2);
    a.join();
    b.join();
}
