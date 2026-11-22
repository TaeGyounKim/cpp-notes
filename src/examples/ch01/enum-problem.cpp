#include <print>

// 컵 크기를 정수 상수로 나타낸 코드.
// const는 "값을 바꿀 수 없음"이라는 표시 (뒤의 글에서 다룸)
const int SizeSmall{ 0 };
const int SizeMedium{ 1 };
const int SizeLarge{ 2 };

int main()
{
    int size{ SizeSmall };

    size = size + 5;   // 크기에 5를 더한다? 뜻이 없지만 컴파일된다.
    std::println("{}", size);

    size = -1;         // 어느 크기도 아닌 값. 역시 컴파일된다.
    std::println("{}", size);
}
