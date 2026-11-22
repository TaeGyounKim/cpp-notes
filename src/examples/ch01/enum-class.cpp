#include <print>
#include <utility>

enum class CupSize { Small, Medium, Large };

// 값을 직접 정할 수도 있다. 정하지 않은 열거자는 "앞의 값 + 1"
enum class HttpStatus
{
    Ok = 200,
    Created,            // 201
    NotFound = 404,
    MethodNotAllowed    // 405
};

int main()
{
    CupSize size{ CupSize::Medium };

    // size = size + 5;   // 오류: 열거형은 정수처럼 계산할 수 없다.
    // size = -1;         // 오류: 정수를 넣을 수 없다.
    // int n{ size };     // 오류: 정수로 자동 변환되지 않는다.

    // 내부의 정수 값을 꺼내려면 직접 요청해야 한다.
    std::println("{}", std::to_underlying(size));
    std::println("{}", std::to_underlying(CupSize::Large));
    std::println("{} {}", std::to_underlying(HttpStatus::Created),
                 std::to_underlying(HttpStatus::MethodNotAllowed));

    size = CupSize::Large;
    std::println("{}", size == CupSize::Large);
}
