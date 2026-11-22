// "오류와 예외" 글의 시각화: check()가 던진 예외가 total()을 건너뛰어 main()의 catch로 간다.
// 스택 칸 하나가 함수 호출 하나(스택 프레임)다. 아래로 갈수록 나중에 부른 함수.
// 예외 객체의 주소는 설명을 위해 지어낸 값이다. 그림이 작아지지 않게 코드 줄을 짧게 썼다.

const main = { id: 'main', name: 'main()', type: '프레임' };
const total = { id: 'total', name: 'total(3, -1)', type: '프레임' };
const c1 = { id: 'c1', name: 'check(3)', type: '프레임' };
const c2 = { id: 'c2', name: 'check(-1)', type: '프레임' };
const ex = { id: 'ex', name: '예외 객체', type: 'domain_error', value: '"음수"', addr: '0x7c0' };
const e = { id: 'e', name: 'e', type: 'const exception&', pointsTo: 'ex' };

export default {
	regions: { stack: '호출 스택', heap: '예외 객체' },
	code: `int check(int v)
{
    if (v < 0)
        throw std::domain_error{"음수"};
    return v;
}

int total(int a, int b)
{
    return check(a) + check(b);
}

int main()
{
    try {
        total(3, -1);
    } catch (const std::exception& e) {
        std::println("{}", e.what());
    }
}`,
	steps: [
		{
			line: 16,
			note: 'main()이 try 블록 안에서 total()을 부름',
			stack: [main],
		},
		{
			line: 10,
			note: 'total()이 check(a)를 부름',
			stack: [main, total],
		},
		{
			line: 5,
			note: 'check(3) 실행 중. 음수가 아니므로 3을 돌려줌. 돌아가면 이 프레임은 사라짐',
			stack: [main, total, c1],
		},
		{
			line: 3,
			note: '이번에는 check(b), 즉 check(-1)을 부름. v가 음수',
			stack: [main, total, c2],
		},
		{
			line: 4,
			note: 'throw: 예외 객체를 만들고 정상 흐름을 멈춤. 가장 가까운 처리기를 찾아 호출 스택을 거슬러 올라감',
			stack: [main, total, c2],
			heap: [ex],
		},
		{
			line: 17,
			note: 'check()와 total()에는 처리기가 없으므로 두 프레임이 모두 풀려 사라짐(스택 풀기). total()의 덧셈은 끝나지 못함. main()의 catch가 예외를 잡고 e가 예외 객체를 가리킴',
			stack: [{ ...main, value: 'catch 중' }, e],
			heap: [ex],
		},
		{
			line: 18,
			note: 'e.what()으로 이유를 꺼내 출력함. catch 블록이 끝나면 예외 객체도 사라짐',
			stack: [{ ...main, value: 'catch 중' }, e],
			heap: [ex],
		},
	],
};
