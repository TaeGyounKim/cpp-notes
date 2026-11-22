// "directed_graph 설계와 기본 연산" 글의 시각화: 노드를 지우면 뒤 노드의 인덱스가 당겨지므로
// 모든 인접 집합의 인덱스도 고쳐야 한다. 예제 graph-basic.cpp의 erase()와 같은 순서다.

const node = (k, value, targets, label = k) => ({
	id: `n${value}`,
	name: `m_nodes[${label}]`,
	type: 'node',
	value: `${value} → {${targets.join(', ')}}`,
});
const key = (k) => ({ id: 'k', name: 'k', type: 'size_t', value: String(k) });

export default {
	regions: { stack: 'erase("B")의 k와 m_nodes (값 → 나가는 간선의 인덱스)' },
	code: `bool erase(const T& v)
{
    auto k{ index_of(v) };
    if (!k) { return false; }
    for (node& n : m_nodes) {
        // k는 빼고, k보다 크면 -1
    }
    m_nodes.erase(begin + *k);
    return true;
}`,
	steps: [
		{
			line: 1,
			note: '지우기 전: A는 B(1), C(2)로, B는 C(2)로, C는 A(0)로, D는 C(2)로 간선이 있음',
			stack: [node(0, 'A', [1, 2]), node(1, 'B', [2]), node(2, 'C', [0]), node(3, 'D', [2])],
		},
		{
			line: 3,
			note: 'B의 인덱스를 찾음: k = 1',
			stack: [key(1), node(0, 'A', [1, 2]), node(1, 'B', [2]), node(2, 'C', [0]), node(3, 'D', [2])],
		},
		{
			line: 6,
			note: 'A: 1(B로 가는 간선)은 없애고, 2는 1보다 크므로 1로 줄임 → {1}',
			stack: [key(1), node(0, 'A', [1]), node(1, 'B', [2]), node(2, 'C', [0]), node(3, 'D', [2])],
		},
		{
			line: 6,
			note: 'B: 2 → 1. B는 곧 지워지므로 결과는 상관없음. C: 0은 k보다 작아 그대로',
			stack: [key(1), node(0, 'A', [1]), node(1, 'B', [1]), node(2, 'C', [0]), node(3, 'D', [2])],
		},
		{
			line: 6,
			note: 'D: 2 → 1. 이제 모든 인덱스가 "B가 빠진 뒤의 위치"를 가리킴',
			stack: [key(1), node(0, 'A', [1]), node(1, 'B', [1]), node(2, 'C', [0]), node(3, 'D', [1])],
		},
		{
			line: 8,
			note: 'vector에서 B를 지움: C와 D가 한 칸씩 앞으로 와 인덱스 1, 2가 됨. A → {1}은 C를, D → {1}도 C를 가리킴',
			stack: [key(1), node(0, 'A', [1]), node(1, 'C', [0], 1), node(2, 'D', [1], 2)],
		},
		{
			line: 9,
			note: '결과: A → C, C → A, D → C. 값으로 보면 B와 관련된 간선만 사라짐',
			stack: [node(0, 'A', [1]), node(1, 'C', [0], 1), node(2, 'D', [1], 2)],
		},
	],
};
