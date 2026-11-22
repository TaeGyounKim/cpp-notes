// "이 사이트 사용법" 글의 시각화 시연용 데이터.

const a = (value) => ({ id: 'a', name: 'a', type: 'int', addr: '0x100', value });
const b = (value) => ({ id: 'b', name: 'b', type: 'int', addr: '0x104', value });

export default {
	code: `int main()
{
    int a{ 1 };
    int b{ 2 };
    a = a + b;
    b = a * 10;
}`,
	steps: [
		{ line: 3, note: '변수 a가 만들어지고 1이 들어갑니다.', stack: [a('1')] },
		{ line: 4, note: '변수 b가 만들어지고 2가 들어갑니다.', stack: [a('1'), b('2')] },
		{ line: 5, note: 'a + b를 계산한 3이 a에 들어갑니다. 값이 바뀐 칸은 잠깐 색이 번쩍입니다.', stack: [a('3'), b('2')] },
		{ line: 6, note: 'a * 10을 계산한 30이 b에 들어갑니다.', stack: [a('3'), b('30')] },
	],
};
