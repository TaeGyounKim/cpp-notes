// "동적 메모리 다루기" 글의 시각화: 스택과 자유 저장소, 포인터의 포인터, 누수.
// 주소는 설명을 위해 지어낸 값이다.

const i = { id: 'i', name: 'i', type: 'int', addr: '0x100', value: '7' };
const ptr = (extra) => ({ id: 'ptr', name: 'ptr', type: 'int*', addr: '0x108', ...extra });
const handle = { id: 'handle', name: 'handle', type: 'int**', addr: '0x110', pointsTo: 'h2' };
const h1 = (value, freed) => ({ id: 'h1', type: 'int', addr: '0x9a0', value, freed });
const h2 = (extra) => ({ id: 'h2', type: 'int*', addr: '0x9b0', ...extra });
const h3 = { id: 'h3', type: 'int', addr: '0x9c0', value: '9' };

export default {
	code: `void f()
{
    int i{ 7 };
    int* ptr{ new int };
    *ptr = 8;
    int** handle{ new int* };
    *handle = new int{ 9 };
    delete ptr;
    ptr = nullptr;
}`,
	steps: [
		{
			line: 3,
			note: '지역 변수 i는 스택에 생김. 함수가 끝나면 저절로 사라지는 자동 변수',
			stack: [i],
		},
		{
			line: 4,
			note: 'new는 자유 저장소에 int 칸을 잡고 주소를 돌려줌. 초기화하지 않았으므로 값은 알 수 없음(?). 포인터 ptr 자체는 스택에 있음',
			stack: [i, ptr({ pointsTo: 'h1' })],
			heap: [h1('?')],
		},
		{
			line: 5,
			note: 'ptr이 가리키는 칸에 8을 씀',
			stack: [i, ptr({ pointsTo: 'h1' })],
			heap: [h1('8')],
		},
		{
			line: 6,
			note: '"int를 가리키는 포인터"를 담을 칸을 자유 저장소에 잡음. 포인터도 자유 저장소에 있을 수 있음. 아직 아무것도 가리키지 않음(?)',
			stack: [i, ptr({ pointsTo: 'h1' }), handle],
			heap: [h1('8'), h2({ value: '?' })],
		},
		{
			line: 7,
			note: '그 칸(*handle)에 새 int 칸의 주소를 넣음. 스택의 handle → 자유 저장소의 포인터 → 자유 저장소의 int. 두 단계의 포인터',
			stack: [i, ptr({ pointsTo: 'h1' }), handle],
			heap: [h1('8'), h2({ pointsTo: 'h3' }), h3],
		},
		{
			line: 8,
			note: 'delete로 ptr이 가리키던 칸을 돌려줌. ptr에 든 주소는 그대로라서, 이제 사라진 칸을 가리킴',
			stack: [i, ptr({ pointsTo: 'h1' }), handle],
			heap: [h1('8', true), h2({ pointsTo: 'h3' }), h3],
		},
		{
			line: 9,
			note: 'ptr을 nullptr로 비워서, 돌려준 칸을 실수로 쓰지 않게 함',
			stack: [i, ptr({ value: 'nullptr' }), handle],
			heap: [h1('8', true), h2({ pointsTo: 'h3' }), h3],
		},
		{
			line: 10,
			note: '함수가 끝나 스택의 변수가 모두 사라짐. 자유 저장소의 두 칸은 해제되지 않았고, 이제 그 칸에 닿을 길이 없음. 메모리 누수',
			stack: [],
			heap: [h1('8', true), h2({ pointsTo: 'h3' }), h3],
		},
	],
};
