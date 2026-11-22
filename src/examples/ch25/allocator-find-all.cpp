#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>
#include <memory>
#include <memory_resource>
#include <print>
#include <string>
#include <vector>

// 조건을 만족하는 "모든" 원소의 반복자를 출력 반복자에 쓴다.
// 범위 알고리즘처럼 끝을 센티널로 받고, 프로젝션을 지원한다.
template <std::forward_iterator It, std::sentinel_for<It> S,
          std::output_iterator<It> Out, typename Proj = std::identity,
          std::indirect_unary_predicate<std::projected<It, Proj>> Pred>
Out find_all(It first, S last, Out dest, Pred pred, Proj proj = {})
{
    for (; first != last; ++first) {
        if (std::invoke(pred, std::invoke(proj, *first))) {
            *dest = first;
            ++dest;
        }
    }
    return dest;
}

struct Task {
    std::string name;
    int priority;
};

int main()
{
    // 할당자: 초기화되지 않은 메모리만 잡고, 생성·소멸은 따로 한다.
    std::allocator<std::string> alloc;
    std::string* raw{ alloc.allocate(2) };
    std::construct_at(raw, "first");          // 그 자리에 생성(C++20)
    std::construct_at(raw + 1, "second");
    std::println("{} {}", raw[0], raw[1]);
    std::destroy_n(raw, 2);                    // 소멸자 호출
    alloc.deallocate(raw, 2);                  // 메모리 반환

    // 다형 할당자: 스택 버퍼에서 잡는 vector. 타입은 pmr::vector 하나
    std::byte buffer[256];
    std::pmr::monotonic_buffer_resource pool{ buffer, sizeof buffer };
    std::pmr::vector<int> nums{ { 3, 1, 4, 1, 5 }, &pool };
    // 복사본은 기본 자원(힙)을 쓰지만 타입은 같다.
    std::pmr::vector<int> other{ nums };
    std::println("{} / {}", nums, other);

    // find_all: 반복자를 모아 위치까지 알 수 있다.
    std::vector<int> values{ 5, 4, 5, 4, 10, 6, 5, 8, 10 };
    std::vector<std::vector<int>::iterator> hits;
    find_all(values.begin(), values.end(), std::back_inserter(hits),
             [](int v) { return v == 10; });
    for (auto it : hits) {
        std::println("10 at {}", std::distance(values.begin(), it));
    }

    // 프로젝션: 멤버를 꺼내 술어에 넘긴다.
    std::vector<Task> tasks{ { "build", 2 }, { "test", 5 }, { "ship", 5 } };
    std::vector<std::vector<Task>::iterator> urgent;
    find_all(tasks.begin(), tasks.end(), std::back_inserter(urgent),
             [](int p) { return p >= 5; }, &Task::priority);
    for (auto it : urgent) { std::println("급함: {}", it->name); }
}
