#include <optional>
#include <print>

// 회원 등급에 맞는 할인율을 돌려준다. 할인이 없는 등급이면 "값 없음".
std::optional<int> findDiscount(char grade)
{
    if (grade == 'A') {
        return 20;
    }
    if (grade == 'B') {
        return 10;
    }
    return std::nullopt;   // 값 없음. return {}; 로 적어도 같다.
}

int main()
{
    std::optional<int> gold{ findDiscount('A') };
    std::optional<int> guest{ findDiscount('Z') };

    // 값이 있는지 확인하는 두 가지 방법
    std::println("gold에 값이 있는가: {}", gold.has_value());
    if (!guest) {
        std::println("guest에는 값이 없다.");
    }

    // 값을 꺼내는 두 가지 방법
    std::println("{}", gold.value());
    std::println("{}", *gold);

    // 값이 없으면 대신 쓸 값을 정해 둔다.
    std::println("{}", guest.value_or(0));
}
