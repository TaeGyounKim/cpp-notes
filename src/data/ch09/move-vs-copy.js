// "우측값 참조와 이동 의미론" 글의 시각화: 복사는 배열을 새로 만들고, 이동은 배열의 주인만 바꾼다.
// 주소는 설명을 위해 지어낸 값이다. 너비·높이 멤버는 생략하고 m_cells만 그린다.

const a = (extra) => ({ id: 'a', name: 'a.m_cells', type: 'double*', addr: '0x100', ...extra });
const b = (extra) => ({ id: 'b', name: 'b.m_cells', type: 'double*', addr: '0x0e0', ...extra });
const c = (extra) => ({ id: 'c', name: 'c.m_cells', type: 'double*', addr: '0x0c0', ...extra });
const arr = { id: 'h', name: '12칸', type: 'double[12]', addr: '0x9a0' };
const copy = { id: 'hc', name: '12칸 사본', type: 'double[12]', addr: '0xa40' };

export default {
	code: `Grid a{ 4, 3 };
Grid b{ a };
Grid c{ std::move(a) };`,
	steps: [
		{
			line: 1,
			note: 'a가 12칸 배열을 가짐',
			stack: [a({ pointsTo: 'h' })],
			heap: [arr],
		},
		{
			line: 2,
			note: '복사 생성자: 새 12칸 배열을 잡고 값을 하나하나 복사함. 메모리 할당과 복사가 필요함',
			stack: [a({ pointsTo: 'h' }), b({ pointsTo: 'hc' })],
			heap: [arr, copy],
		},
		{
			line: 3,
			note: '이동 생성자: 새 배열을 잡지 않음. a의 포인터를 c가 가져가고(얕은 복사), a는 nullptr로 비움. 배열의 주인만 바뀜. 소멸할 때 지우는 것은 c 하나뿐이라 이중 해제가 없음',
			stack: [a({ value: 'nullptr' }), b({ pointsTo: 'hc' }), c({ pointsTo: 'h' })],
			heap: [arr, copy],
		},
	],
};
