#include <memory>
#include <print>

// C 라이브러리라고 치자. 여는 함수와 닫는 함수를 짝으로 불러야 한다.
struct Connection
{
    int id;
};

Connection* open_connection(int id)
{
    std::println("  연결 {} 열림", id);
    return new Connection{ id };
}

void close_connection(Connection* connection)
{
    std::println("  연결 {} 닫힘", connection->id);
    delete connection;
}

int main()
{
    std::println("C 스타일 배열");
    std::size_t count{ 4 };
    auto scores{ std::make_unique<int[]>(count) };   // 모두 0으로 초기화
    scores[1] = 95;
    for (std::size_t i{ 0 }; i < count; ++i) {
        std::print("{} ", scores[i]);
    }
    std::println("");

    std::println("사용자 정의 삭제자");
    {
        // 둘째 템플릿 인수: 삭제자의 타입(여기서는 함수 포인터 타입)
        std::unique_ptr<Connection, decltype(&close_connection)> connection{
            open_connection(7), close_connection
        };
        std::println("  연결 {} 사용 중", connection->id);
    }   // 범위를 벗어나면 delete 대신 close_connection을 부른다.
    std::println("끝");
}
