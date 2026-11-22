// "포인터와 동적 메모리" 글의 첫 번째 시각화: 포인터는 주소를 담는 변수.
// 주소는 설명을 위해 지어낸 값이다.

const score = (value) => ({ id: 'score', name: 'score', type: 'int', addr: '0x100', value });
const bonus = (value) => ({ id: 'bonus', name: 'bonus', type: 'int', addr: '0x104', value });
const p = (pointsTo) => ({ id: 'p', name: 'p', type: 'int*', addr: '0x108', pointsTo });

export default {
	code: `int main()
{
    int score{ 8 };
    int bonus{ 3 };
    int* p{ &score };
    *p = 10;
    p = &bonus;
    *p = 5;
}`,
	steps: [
		{
			line: 3,
			note: 'int 변수 score. 주소 0x100에 놓임',
			stack: [score('8')],
		},
		{
			line: 4,
			note: 'int 변수 bonus. 주소 0x104에 놓임',
			stack: [score('8'), bonus('3')],
		},
		{
			line: 5,
			note: '&score는 score의 주소 0x100. 그 주소가 포인터 p에 들어감. 화살표는 "p가 score를 가리킨다"는 뜻',
			stack: [score('8'), bonus('3'), p('score')],
		},
		{
			line: 6,
			note: '*p는 p가 가리키는 칸, 즉 score. p 자체가 아니라 score의 값이 10으로 바뀜',
			stack: [score('10'), bonus('3'), p('score')],
		},
		{
			line: 7,
			note: '별표 없이 p에 대입하면 p에 든 주소가 바뀜. 이제 p는 bonus를 가리킴. score와 bonus의 값은 그대로',
			stack: [score('10'), bonus('3'), p('bonus')],
		},
		{
			line: 8,
			note: '같은 *p = ... 이지만 이번에는 bonus가 바뀜. p가 가리키는 곳이 달라졌기 때문',
			stack: [score('10'), bonus('5'), p('bonus')],
		},
	],
};
