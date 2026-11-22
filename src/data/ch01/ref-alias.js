// "참조" 글의 첫 번째 시각화: 참조는 새 칸이 아니라 이미 있는 칸의 다른 이름.

const x = (value, aliases) => ({ id: 'x', name: 'x', type: 'int', addr: '0x100', value, aliases });
const y = (value) => ({ id: 'y', name: 'y', type: 'int', addr: '0x104', value });

export default {
	code: `int main()
{
    int x{ 3 };
    int y{ 4 };
    int& ref{ x };
    ref = 10;
    ref = y;
    y = 99;
}`,
	steps: [
		{
			line: 3,
			note: 'int 변수 x',
			stack: [x('3')],
		},
		{
			line: 4,
			note: 'int 변수 y',
			stack: [x('3'), y('4')],
		},
		{
			line: 5,
			note: '참조 ref는 새 칸을 만들지 않음. 이미 있는 x 칸에 ref라는 이름이 하나 더 붙을 뿐',
			stack: [x('3', ['ref']), y('4')],
		},
		{
			line: 6,
			note: 'ref에 대입하는 것은 x에 대입하는 것과 완전히 같음. x가 10이 됨',
			stack: [x('10', ['ref']), y('4')],
		},
		{
			line: 7,
			note: 'ref가 y 쪽으로 옮겨 가는 것이 아님. y의 값 4를 ref, 즉 x에 넣는 대입. 별명은 여전히 x에 붙어 있음',
			stack: [x('4', ['ref']), y('4')],
		},
		{
			line: 8,
			note: 'y를 바꿔도 x와 ref는 그대로 4. ref는 y와 아무 관계가 없음',
			stack: [x('4', ['ref']), y('99')],
		},
	],
};
