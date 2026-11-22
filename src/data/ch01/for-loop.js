// "반복문, 초기화 리스트, 문자열" 글의 시각화: for 문이 도는 순서.

const total = (value) => ({ id: 'total', name: 'total', type: 'int', addr: '0x100', value });
const i = (value) => ({ id: 'i', name: 'i', type: 'int', addr: '0x104', value });

export default {
	code: `int main()
{
    int total{ 0 };
    for (int i{ 1 }; i <= 3; ++i) {
        total += i;
    }
}`,
	steps: [
		{
			line: 3,
			note: '합을 담을 total. 0으로 시작',
			stack: [total('0')],
		},
		{
			line: 4,
			note: '시작: i를 만들고 1을 넣음. 이 부분은 맨 처음 한 번만 실행됨. 이어서 조건 i <= 3을 검사. 1 <= 3은 참이므로 블록으로 들어감',
			stack: [total('0'), i('1')],
		},
		{
			line: 5,
			note: '첫 번째 바퀴. 0 + 1 = 1',
			stack: [total('1'), i('1')],
		},
		{
			line: 4,
			note: '블록이 끝나면 ++i가 실행되어 i는 2. 다시 조건 검사. 2 <= 3은 참',
			stack: [total('1'), i('2')],
		},
		{
			line: 5,
			note: '두 번째 바퀴. 1 + 2 = 3',
			stack: [total('3'), i('2')],
		},
		{
			line: 4,
			note: '++i로 i는 3. 3 <= 3은 참',
			stack: [total('3'), i('3')],
		},
		{
			line: 5,
			note: '세 번째 바퀴. 3 + 3 = 6',
			stack: [total('6'), i('3')],
		},
		{
			line: 4,
			note: '++i로 i는 4. 4 <= 3은 거짓이므로 반복을 끝냄',
			stack: [total('6'), i('4')],
		},
		{
			line: 7,
			note: 'for 문이 끝나면 i는 사라짐. total에는 1 + 2 + 3 = 6이 남음',
			stack: [total('6')],
		},
	],
};
