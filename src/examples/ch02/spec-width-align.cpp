#include <print>
#include <string>

int main()
{
    int number{ 42 };
    std::string word{ "cat" };

    // 너비: 최소 몇 칸을 차지할지
    std::println("|{:7}|", number);   // 숫자는 기본이 오른쪽 정렬
    std::println("|{:7}|", word);     // 문자열은 기본이 왼쪽 정렬

    // 정렬: < 왼쪽, > 오른쪽, ^ 가운데
    std::println("|{:<7}|", number);
    std::println("|{:>7}|", word);
    std::println("|{:^7}|", number);

    // 채움 문자: 정렬 기호 앞에 적는다.
    std::println("|{:_>7}|", number);
    std::println("|{:*^7}|", number);

    // 너비를 인수로 받기 (동적 너비)
    std::println("|{:{}}|", number, 10);
    std::println("|{1:{0}}|", 10, number);

    // 응용: 같은 글자를 원하는 개수만큼 출력
    std::println("{:=>20}", "");
}
