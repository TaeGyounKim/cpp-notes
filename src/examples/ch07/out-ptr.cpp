#include <memory>
#include <print>

// C 방식 API: 반환값은 오류 코드, 결과는 출력 매개변수(포인터의 포인터)로
using ErrorCode = int;

ErrorCode create_buffer(int size, int** out)
{
    *out = new int[size]{};
    std::println("  버퍼 {}칸 만듦", size);
    return 0;
}

void destroy_buffer(int* buffer)
{
    std::println("  버퍼 지움");
    delete[] buffer;
}

int main()
{
    std::unique_ptr<int, decltype(&destroy_buffer)> buffer{
        nullptr, destroy_buffer
    };

    // std::out_ptr: 스마트 포인터를 "포인터의 포인터" 자리에 넘긴다.
    // 함수가 돌아오면 받은 포인터를 스마트 포인터에 담아 준다.
    if (create_buffer(8, std::out_ptr(buffer)) == 0) {
        buffer.get()[0] = 42;
        std::println("  첫 칸: {}", buffer.get()[0]);
    }
}
