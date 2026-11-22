#include <cstddef>
#include <iterator>
#include <print>

// 세 선언은 모두 같다. 매개변수의 배열은 포인터로 바뀐다.
// 대괄호 안의 수는 무시된다.
void doubleAll(int* values, std::size_t size);
void doubleAll(int values[], std::size_t size);
void doubleAll(int values[2], std::size_t size);

void doubleAll(int values[], std::size_t size)
{
    // 매개변수 values는 포인터다. sizeof는 배열이 아니라 포인터의 크기.
    // 컴파일러도 이 실수를 경고한다.
    std::println("  함수 안 sizeof(values) = {}", sizeof(values));
    for (std::size_t i{ 0 }; i < size; ++i) {
        values[i] *= 2;   // 복사본이 아니라 원래 배열을 바꾼다.
    }
}

// 배열의 참조로 받으면 크기가 타입에 남는다. 템플릿이 N을 알아낸다.
template <std::size_t N>
void printAll(const int (&values)[N])
{
    for (int value : values) {
        std::print("{} ", value);
    }
    std::println("(원소 {}개)", N);
}

int main()
{
    int scores[]{ 5, 7, 9, 11 };
    std::println("main의 sizeof(scores) = {}", sizeof(scores));

    // 배열 이름은 0번 원소를 가리키는 포인터로 바뀐다(배열의 붕괴).
    int* first{ scores };
    first[1] = 8;

    doubleAll(scores, std::size(scores));     // 배열 이름을 그대로
    doubleAll(&scores[0], std::size(scores)); // 0번 원소의 주소를 직접
    printAll(scores);

    int* fromFreeStore{ new int[3]{ 1, 2, 3 } };
    doubleAll(fromFreeStore, 3);
    // printAll(fromFreeStore);   // 컴파일 오류: 포인터에는 크기가 없다.
    delete[] fromFreeStore;
    fromFreeStore = nullptr;
}
