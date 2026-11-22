// "friend와 객체 안의 동적 메모리" 글의 시각화 2: 얕은 대입으로 메모리가 새고, 두 객체가 한 배열을 나눠 가지는 과정.
// 주소는 설명을 위해 지어낸 값이다.

const a = (extra) => ({ id: 'a', name: 'a.m_cells', type: 'double*', addr: '0x100', ...extra });
const b = (extra) => ({ id: 'b', name: 'b.m_cells', type: 'double*', addr: '0x0e0', ...extra });
const small = { id: 'sa', name: '2칸', type: 'double[2]', addr: '0x9a0' };
const big = { id: 'sb', name: '6칸', type: 'double[6]', addr: '0x9c0' };

export default {
	code: `Grid a{ 1, 2 };
Grid b{ 3, 2 };
a = b;`,
	steps: [
		{
			line: 1,
			note: 'a가 두 칸짜리 배열을 가짐',
			stack: [a({ pointsTo: 'sa' })],
			heap: [small],
		},
		{
			line: 2,
			note: 'b가 여섯 칸짜리 배열을 가짐. 각자 자기 배열이 하나씩',
			stack: [a({ pointsTo: 'sa' }), b({ pointsTo: 'sb' })],
			heap: [small, big],
		},
		{
			line: 3,
			note: '컴파일러가 만든 대입 연산자는 b.m_cells의 주소를 a.m_cells에 덮어씀. 그 결과 (1) a가 원래 가리키던 두 칸짜리 배열은 아무도 가리키지 않아 지울 방법이 없음(메모리 누수). (2) a와 b가 같은 배열을 가리킴. 둘이 소멸할 때 같은 배열을 두 번 지우게 됨',
			stack: [a({ pointsTo: 'sb' }), b({ pointsTo: 'sb' })],
			heap: [{ ...small, name: '2칸(주인 없음)' }, big],
		},
	],
};
