#include <print>
#include <vector>

// is-a: 스택은 vector이다?
// vector를 물려받으면 vector의 공개 멤버 함수가 전부 딸려 온다.
class StackIsA : public std::vector<int>
{
public:
    void push(int value) { push_back(value); }
    void pop() { pop_back(); }
    int top() const { return back(); }
};

// has-a: 스택은 vector를 가진다.
// 밖에 내놓는 것은 스택다운 연산뿐이다.
class StackHasA
{
public:
    void push(int value) { m_values.push_back(value); }
    void pop() { m_values.pop_back(); }
    int top() const { return m_values.back(); }
    bool isEmpty() const { return m_values.empty(); }

private:
    std::vector<int> m_values;   // 구현. 나중에 다른 것으로 바꿔도 된다.
};

int main()
{
    StackIsA a;
    a.push(1);
    a.push(2);
    a.push(3);
    // 스택의 규칙(맨 위에서만 넣고 뺀다)을 깨는 일이 그대로 컴파일된다.
    a.insert(a.begin(), 99);
    a[1] = 0;
    std::println("is-a 스택의 내용: {}", static_cast<std::vector<int>&>(a));

    StackHasA b;
    b.push(1);
    b.push(2);
    b.push(3);
    // b.insert(...);   // 컴파일 오류: 그런 멤버가 없다.
    std::println("has-a 스택의 맨 위: {}", b.top());
}
