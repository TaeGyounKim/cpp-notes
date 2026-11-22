// "deque, list, forward_list, array" 글의 시각화: splice_after는 노드를 복사하지 않고
// 다음 노드를 가리키는 포인터만 바꿔 다른 리스트로 옮긴다. 주소는 설명을 위해 지어낸 값이다.

const head = (id, to) => ({ id, name: id, type: 'forward_list<int>', pointsTo: to, value: '비었음' });
const node = (k, addr, to) => ({
	id: `n${k}`,
	name: `값 ${k}`,
	type: '노드(다음 포인터)',
	addr,
	pointsTo: to,
	value: 'nullptr',
});
const n5 = (to) => node(5, '0x9a0', to);
const n6 = node(6, '0x9c0');
const n1 = (to) => node(1, '0xa40', to);
const n2 = (to) => node(2, '0xa60', to);
const n0 = node(0, '0xb00', 'n1');

export default {
	regions: { stack: '리스트 객체', heap: '노드(자유 공간)' },
	code: `std::forward_list<int> a{ 5, 6 };
std::forward_list<int> b{ 1, 2 };
a.splice_after(a.before_begin(), b);
a.push_front(0);`,
	steps: [
		{
			line: 1,
			note: 'a의 노드 둘. 각 노드는 값과 다음 노드의 주소만 가짐(단일 연결). 노드 칸 오른쪽에 적힌 것이 다음 노드의 주소이고, 마지막 노드의 다음은 nullptr',
			stack: [head('a', 'n5')],
			heap: [n5('n6'), n6],
		},
		{
			line: 2,
			note: 'b의 노드 둘은 자유 공간의 다른 곳에 있음',
			stack: [head('a', 'n5'), head('b', 'n1')],
			heap: [n5('n6'), n6, n1('n2'), n2()],
		},
		{
			line: 3,
			note: 'b의 노드를 a의 맨 앞(before_begin 다음)에 이음. 바뀌는 것은 포인터 셋뿐: a의 시작이 값 1을, 값 2의 다음이 값 5를 가리키고, b는 비게 됨. 노드의 주소가 그대로라는 것은 원소를 복사하지도 옮기지도 않았다는 뜻. 단방향이라 b의 마지막 노드를 찾느라 b의 길이만큼 걸림(양방향인 list::splice는 상수 시간)',
			stack: [head('a', 'n1'), head('b')],
			heap: [n1('n2'), n2('n5'), n5('n6'), n6],
		},
		{
			line: 4,
			note: '맨 앞에 넣기는 새 노드 하나를 만들고 포인터 둘을 바꾸면 끝. 다른 노드는 그대로',
			stack: [head('a', 'n0'), head('b')],
			heap: [n0, n1('n2'), n2('n5'), n5('n6'), n6],
		},
	],
};
