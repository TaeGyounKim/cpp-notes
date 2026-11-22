// "리터럴과 변수" 글의 시각화: 초기화한 변수와 하지 않은 변수.

const count = (value) => ({ id: 'count', name: 'count', type: 'int', addr: '0x100', value });
const total = (value) => ({ id: 'total', name: 'total', type: 'int', addr: '0x104', value });
const empty = (value) => ({ id: 'empty', name: 'empty', type: 'int', addr: '0x108', value });

export default {
	code: `int main()
{
    int count;
    int total{ 7 };
    int empty{};
    count = 3;
    total = total + count;
}`,
	steps: [
		{
			line: 3,
			note: '칸은 생겼지만 값을 넣지 않음. 그 자리에 원래 있던 알 수 없는 값(쓰레기 값)이 그대로 남아 있음',
			stack: [count('???')],
		},
		{
			line: 4,
			note: '칸을 만들면서 7을 넣음. 이것이 초기화',
			stack: [count('???'), total('7')],
		},
		{
			line: 5,
			note: '빈 중괄호로 초기화하면 0이 들어감',
			stack: [count('???'), total('7'), empty('0')],
		},
		{
			line: 6,
			note: '이제야 count에 값이 들어감. 이 줄 전에 count를 읽었다면 쓰레기 값을 읽었을 것',
			stack: [count('3'), total('7'), empty('0')],
		},
		{
			line: 7,
			note: 'total + count를 계산한 10이 total에 들어감',
			stack: [count('3'), total('10'), empty('0')],
		},
	],
};
