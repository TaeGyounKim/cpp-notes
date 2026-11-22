#include <functional>
#include <print>
#include <ranges>
#include <string>
#include <vector>

int main()
{
    // 반복자로 훑고 고치기, const 반복자로 읽기
    std::vector<std::string> rooms(3, "방");
    for (auto it{ rooms.begin() }; it != rooms.end(); ++it) {
        it->append("!");                        // ->로 멤버 함수 호출
    }
    for (auto it{ rooms.cbegin() }; it != rooms.cend(); ++it) {
        std::print("{} ", *it);                 // *it = "x"; 는 컴파일 오류
    }
    std::println("");

    // 임의 접근 반복자: 앞뒤로 건너뛴다.
    std::vector<int> v(10);
    auto it{ v.begin() };
    it += 5;
    --it;
    *it = 4;                                    // 위치 4
    std::println("{}", v);

    // 참조를 담는 vector
    std::string first{ "거실" };
    std::string second{ "부엌" };
    std::vector<std::reference_wrapper<std::string>> refs{ std::ref(first) };
    refs.push_back(std::ref(second));
    refs[1].get() += "(수리 중)";               // second가 바뀐다.
    std::println("{} {}", first, second);

    // 넣기와 지우기
    std::vector nums{ 1, 2, 3, 5 };
    nums.insert(nums.cbegin() + 3, 4);          // 4를 5 앞에
    std::vector<int> more{ 6, 7 };
    nums.insert(nums.cend(), more.cbegin(), more.cend());   // 범위 넣기
    nums.append_range(std::views::iota(8, 10));             // C++23
    std::println("넣은 뒤 {}", nums);
    nums.erase(nums.cbegin() + 1, nums.cbegin() + 3);       // [1, 3) 지움
    nums.pop_back();                            // 마지막 하나(돌려주지 않음)
    std::println("지운 뒤 {}", nums);

    std::vector temps{ 21, -99, 23, -99, 22 };
    std::erase(temps, -99);                     // C++20: 값이 같은 것 모두
    std::erase_if(temps, [](int t) { return t > 22; });
    std::println("걸러 지운 뒤 {}", temps);

    // 이동과 제자리 생성
    std::vector<std::string> names;
    std::string label(3, 'a');
    names.push_back(label);                     // 복사
    names.push_back(std::move(label));          // 이동. label은 이제 쓰지 않음
    names.emplace_back(3, 'b');                 // string(3, 'b')를 제자리에
    std::println("{}", names);

    // insert()가 돌려주는 반복자로 다시 얻는다.
    std::vector<int> w{ 10, 20, 30 };
    auto pos{ w.insert(w.begin(), 5) };         // 새 원소를 참조
    std::println("넣은 원소 {}, 그 다음 {}", *pos, *(pos + 1));
}
