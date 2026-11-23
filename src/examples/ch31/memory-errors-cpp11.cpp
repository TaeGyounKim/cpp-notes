#include <cstdio>
#include <iostream>

// std::println(C++23) 대신 printf. 새니타이저는 표준과 상관없이 쓸 수 있다.
// 입력: 0 오류 없음, 1 힙 범위 밖 쓰기, 2 해제 후 사용
int sum_with_off_by_one(int count)
{
    int* values = new int[count];
    for (int i = 0; i <= count; ++i) {
        values[i] = i;
    }
    int sum = values[0] + values[count - 1];
    delete[] values;
    return sum;
}

int main()
{
    int choice = 0;
    std::cin >> choice;
    if (choice == 1) {
        std::printf("%d\n", sum_with_off_by_one(8));
    } else if (choice == 2) {
        int* p = new int(7);
        delete p;
        std::printf("%d\n", *p);
    } else {
        std::printf("ok\n");
    }
}
