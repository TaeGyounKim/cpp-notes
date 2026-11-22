// "배열" 글의 시각화: 자유 저장소의 2차원 배열을 행마다 따로 잡고 거꾸로 돌려주기.
// 주소는 설명을 위해 지어낸 값이다.

const board = (extra) => ({ id: 'board', name: 'board', type: 'char**', addr: '0x100', ...extra });
const p0 = (extra) => ({ id: 'p0', name: 'board[0]', type: 'char*', addr: '0x9a0', ...extra });
const p1 = (extra) => ({ id: 'p1', name: 'board[1]', type: 'char*', addr: '0x9a8', ...extra });
const r0 = (freed) => ({ id: 'r0', type: 'char[3]', addr: '0x9c0', value: 'X . .', freed });
const r1 = (freed) => ({ id: 'r1', type: 'char[3]', addr: '0x9e0', value: '. O .', freed });

export default {
	code: `char** board{ new char*[2] };
board[0] = new char[3]{ 'X', '.', '.' };
board[1] = new char[3]{ '.', 'O', '.' };
delete[] board[0];
delete[] board[1];
delete[] board;
board = nullptr;`,
	steps: [
		{
			line: 1,
			note: '첫째 차원: char* 두 개짜리 배열을 잡음. 아직 어느 행도 가리키지 않음(?). 컴파일러는 행을 대신 잡아 주지 않음',
			stack: [board({ pointsTo: 'p0' })],
			heap: [p0({ value: '?' }), p1({ value: '?' })],
		},
		{
			line: 2,
			note: '0번 행을 따로 잡아 board[0]에 연결',
			stack: [board({ pointsTo: 'p0' })],
			heap: [p0({ pointsTo: 'r0' }), p1({ value: '?' }), r0()],
		},
		{
			line: 3,
			note: '1번 행도 따로 잡음. 행들은 자유 저장소 여기저기에 흩어질 수 있음. 스택의 2차원 배열처럼 한 줄로 이어져 있지 않음',
			stack: [board({ pointsTo: 'p0' })],
			heap: [p0({ pointsTo: 'r0' }), p1({ pointsTo: 'r1' }), r0(), r1()],
		},
		{
			line: 4,
			note: '돌려줄 때는 잡은 순서를 거꾸로. 행부터 하나씩 delete[]',
			stack: [board({ pointsTo: 'p0' })],
			heap: [p0({ pointsTo: 'r0' }), p1({ pointsTo: 'r1' }), r0(true), r1()],
		},
		{
			line: 5,
			note: '1번 행도 돌려줌',
			stack: [board({ pointsTo: 'p0' })],
			heap: [p0({ pointsTo: 'r0' }), p1({ pointsTo: 'r1' }), r0(true), r1(true)],
		},
		{
			line: 6,
			note: '마지막으로 포인터 배열을 돌려줌. 이것을 먼저 지웠다면 행들에 닿을 길이 사라져 누수가 됐을 것',
			stack: [board({ pointsTo: 'p0' })],
			heap: [p0({ pointsTo: 'r0', freed: true }), p1({ pointsTo: 'r1', freed: true }), r0(true), r1(true)],
		},
		{
			line: 7,
			note: 'board를 비움. 남은 메모리 없음',
			stack: [board({ value: 'nullptr' })],
			heap: [p0({ value: '-', freed: true }), p1({ value: '-', freed: true }), r0(true), r1(true)],
		},
	],
};
