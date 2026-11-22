// "참조" 글의 두 번째 시각화: 값으로 받기와 참조로 받기.

const count = (value, aliases) => ({ id: 'count', name: 'count', type: 'main · int', addr: '0x100', value, aliases });
const copy = (value) => ({ id: 'copy', name: 'n', type: 'addOneCopy · int', addr: '0x0e0', value });

export default {
	code: `void addOneCopy(int n) { n++; }
void addOneRef(int& n) { n++; }

int main()
{
    int count{ 7 };
    addOneCopy(count);
    addOneRef(count);
}`,
	steps: [
		{
			line: 6,
			note: 'main의 변수 count',
			stack: [count('7')],
		},
		{
			line: 7,
			note: 'addOneCopy를 호출함',
			stack: [count('7')],
		},
		{
			line: 1,
			note: '값으로 받기: 매개변수 n의 칸이 새로 생기고 count의 값 7이 복사됨',
			stack: [count('7'), copy('7')],
		},
		{
			line: 1,
			note: 'n++는 복사본 n만 8로 바꿈. main의 count는 7 그대로',
			stack: [count('7'), copy('8')],
		},
		{
			line: 8,
			note: '함수가 끝나 n은 사라짐. 바꾼 것도 함께 사라짐. 이번에는 addOneRef를 호출함',
			stack: [count('7')],
		},
		{
			line: 2,
			note: '참조로 받기: 새 칸이 생기지 않음. n은 main의 count에 붙은 다른 이름',
			stack: [count('7', ['n'])],
		},
		{
			line: 2,
			note: 'n++는 곧 count++. main의 count가 8이 됨',
			stack: [count('8', ['n'])],
		},
		{
			line: 9,
			note: '함수가 끝나 별명 n은 사라지지만, 바뀐 값 8은 count에 남음',
			stack: [count('8')],
		},
	],
};
