// "friend와 객체 안의 동적 메모리" 글의 시각화 1: 얕은 복사로 두 객체가 한 배열을 나눠 가지다가 댕글링이 되는 과정.
// 주소는 설명을 위해 지어낸 값이다. Grid의 너비·높이 멤버는 생략하고 m_cells만 그린다.

const room = (extra) => ({ id: 'room', name: 'room.m_cells', type: 'double*', addr: '0x100', ...extra });
const g = (extra) => ({ id: 'g', name: 'g.m_cells', type: 'double*', addr: '0x0e0', ...extra });
const cells = (value, freed) => ({ id: 'c', name: '4칸', type: 'double[4]', addr: '0x9a0', value, freed });

export default {
	code: `void show(Grid g) { /* ... */ }

Grid room{ 2, 2 };
room.set(0, 21.5);
show(room);
room.get(0);`,
	steps: [
		{
			line: 3,
			note: '생성자가 자유 저장소에 double 네 칸을 잡고, 그 주소를 room.m_cells에 넣음',
			stack: [room({ pointsTo: 'c' })],
			heap: [cells('[0]=0')],
		},
		{
			line: 4,
			note: 'room을 통해 첫 칸에 21.5를 씀',
			stack: [room({ pointsTo: 'c' })],
			heap: [cells('[0]=21.5')],
		},
		{
			line: 5,
			note: '값으로 넘기므로 매개변수 g가 복사로 만들어짐. 컴파일러가 만든 복사 생성자는 포인터의 값(주소)만 복사함. 배열은 하나, 가리키는 포인터는 둘',
			stack: [room({ pointsTo: 'c' }), g({ pointsTo: 'c' })],
			heap: [cells('[0]=21.5')],
		},
		{
			line: 1,
			note: 'show가 끝나며 g의 소멸자가 delete[]를 부름. 배열이 지워짐. room은 그 사실을 모름',
			stack: [room({ pointsTo: 'c' })],
			heap: [cells('[0]=21.5', true)],
		},
		{
			line: 6,
			note: 'room.m_cells는 이미 지워진 메모리를 가리키는 댕글링 포인터. 읽으면 정의되지 않은 동작. main이 끝나면 room의 소멸자가 같은 배열을 또 지우려 함(이중 해제)',
			stack: [room({ pointsTo: 'c' })],
			heap: [cells('[0]=21.5', true)],
		},
	],
};
