#include <print>

int main()
{
    int x{ 3 };
    int y{ 4 };

    int& ref{ x };   // ref는 x의 다른 이름
    std::println("x={} ref={}", x, ref);

    ref = 10;        // x가 10이 된다.
    std::println("x={} ref={}", x, ref);

    // ref가 y를 가리키게 되는 것이 아니다. x에 y의 값 4가 들어간다.
    ref = y;
    std::println("x={} y={} ref={}", x, y, ref);

    y = 99;          // ref는 여전히 x의 이름이므로 영향을 받지 않는다.
    std::println("x={} y={} ref={}", x, y, ref);

    // int& empty;   // 오류: 참조는 만들 때 반드시 초기화해야 한다.
}
