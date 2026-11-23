#include <cstdlib>
#include <iostream>
#include <print>

// 주소 새니타이저(-fsanitize=address)로 메모리 오류를 잡아 본다.
// 입력: 0 오류 없음, 1 힙 범위 밖 쓰기, 2 해제 후 사용, 3 두 번 해제,
//       4 스택 배열 범위 밖, 5 new[]를 delete로 해제
int sum_with_off_by_one(int count)
{
    int* values{ new int[count] };
    for (int i{ 0 }; i <= count; ++i) {   // <=: 한 칸 넘침
        values[i] = i;
    }
    int sum{ values[0] + values[count - 1] };
    delete[] values;
    return sum;
}

int main()
{
    int choice{ 0 };
    std::cin >> choice;
    std::println("선택 {}", choice);

    if (choice == 1) {
        std::println("결과 {}", sum_with_off_by_one(8));
    } else if (choice == 2) {
        int* p{ new int{ 7 } };
        delete p;
        std::println("해제한 뒤 읽기 {}", *p);
    } else if (choice == 3) {
        int* p{ new int[4] };
        delete[] p;
        delete[] p;
    } else if (choice == 4) {
        int grid[4]{};
        int index{ 4 };
        grid[index] = 1;
        std::println("{}", grid[0]);
    } else if (choice == 5) {
        int* p{ new int[4] };
        delete p;   // delete[]여야 함
    } else {
        std::println("문제없는 실행");
    }
}
