// "예외, 타입 별칭, 타입 추론" 글의 시각화: 예외가 던져지면 실행이 어디로 가는가.

const a = (value) => ({ id: 'a', name: 'a', type: 'main · int', addr: '0x100', value });
const b = { id: 'b', name: 'b', type: 'main · int', addr: '0x104', value: '???' };
const total = { id: 'total', name: 'total', type: 'average · int', addr: '0x0e0', value: '100' };
const count = (value) => ({ id: 'count', name: 'count', type: 'average · int', addr: '0x0e4', value });

export default {
	code: `int average(int total, int count)
{
    if (count == 0) {
        throw std::invalid_argument{ "zero" };
    }
    return total / count;
}

int main()
{
    try {
        int a{ average(100, 4) };
        int b{ average(100, 0) };
        int c{ average(90, 3) };
    } catch (const std::invalid_argument& e) {
        // 문제를 처리하는 코드
    }
}`,
	steps: [
		{
			line: 12,
			note: 'try 블록 안의 첫 줄. a를 초기화하려고 average(100, 4)를 호출함',
			stack: [a('???')],
		},
		{
			line: 6,
			note: 'count가 0이 아니므로 throw를 지나침. 100 / 4 = 25를 돌려줌',
			stack: [a('???'), total, count('4')],
		},
		{
			line: 12,
			note: '돌려받은 25가 a에 들어감. 여기까지는 보통의 함수 호출',
			stack: [a('25')],
		},
		{
			line: 13,
			note: 'b를 초기화하려고 average(100, 0)을 호출함',
			stack: [a('25'), b],
		},
		{
			line: 4,
			note: 'count가 0이므로 예외를 던짐. 함수는 값을 돌려주지 않고 여기서 즉시 끝남',
			stack: [a('25'), b, total, count('0')],
		},
		{
			line: 15,
			note: '실행이 catch로 곧장 건너뜀. try 블록의 남은 줄(14번 줄)은 실행되지 않음. try 블록 안에서 만든 a와 b도 사라짐',
			stack: [],
		},
		{
			line: 16,
			note: 'catch 블록 안에서 문제를 처리함. e.what()으로 예외에 담긴 설명을 읽을 수 있음',
			stack: [],
		},
		{
			line: 18,
			note: 'catch 블록이 끝나면 그 아래로 정상적으로 이어짐. 프로그램은 죽지 않음',
			stack: [],
		},
	],
};
