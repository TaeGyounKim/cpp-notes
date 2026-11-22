int red{ 255 };

// 열거자 red가 바깥 범위로 나오면서 위의 변수 red와 충돌한다.
enum Signal { red, yellow, green };

int main()
{
}
