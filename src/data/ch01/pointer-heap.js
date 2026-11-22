// "포인터와 동적 메모리" 글의 두 번째 시각화: new, delete, 매달린 포인터.
// 주소는 설명을 위해 지어낸 값이다.

const p = (extra) => ({ id: 'p', name: 'p', type: 'int*', addr: '0x100', ...extra });
const q = { id: 'q', name: 'q', type: 'int*', addr: '0x108', pointsTo: 'h' };
const h = (value, freed) => ({ id: 'h', type: 'int', addr: '0x9a0', value, freed });

export default {
	code: `int main()
{
    int* p{ new int{ 5 } };
    int* q{ p };
    *q = 6;
    delete p;
    p = nullptr;
}`,
	steps: [
		{
			line: 3,
			note: 'new는 자유 저장소에 이름 없는 int 칸을 만들고 그 주소를 돌려줌. 이 칸에 닿는 길은 p에 든 주소뿐',
			stack: [p({ pointsTo: 'h' })],
			heap: [h('5')],
		},
		{
			line: 4,
			note: '포인터를 복사하면 주소가 복사됨. 자유 저장소의 칸은 여전히 하나이고, 그것을 가리키는 화살표가 둘이 됨',
			stack: [p({ pointsTo: 'h' }), q],
			heap: [h('5')],
		},
		{
			line: 5,
			note: 'q를 거쳐 값을 바꿈. p가 가리키는 것도 같은 칸이므로 *p로 읽어도 6',
			stack: [p({ pointsTo: 'h' }), q],
			heap: [h('6')],
		},
		{
			line: 6,
			note: 'delete는 자유 저장소의 칸을 돌려줌. 하지만 p와 q에 든 주소는 지워지지 않음. 둘 다 이미 사라진 칸을 가리키는 "매달린 포인터"가 됨',
			stack: [p({ pointsTo: 'h' }), q],
			heap: [h('6', true)],
		},
		{
			line: 7,
			note: 'p는 nullptr로 비워서 안전해짐. 하지만 q는 여전히 돌려준 칸을 가리킴. 이제 *q를 쓰면 정의되지 않은 동작',
			stack: [p({ value: 'nullptr' }), q],
			heap: [h('6', true)],
		},
	],
};
