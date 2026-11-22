// "vector 반복자와 원소 넣기·지우기" 글의 시각화: 재할당이 일어나면
// 기존 반복자가 옛 버퍼를 가리킨 채 남는다. 주소는 설명을 위해 지어낸 값이다.

const v = (to) => ({ id: 'v', name: 'v', type: 'vector<int>', pointsTo: to });
const it = (to, extra) => ({ id: 'it', name: 'it', type: 'iterator', pointsTo: to, ...extra });
const old = (k, value, freed) => ({ id: `o${k}`, name: `옛 [${k}]`, type: 'int', addr: `0x9a${k * 4}`, value, freed });
const neu = (k, value) => ({ id: `n${k}`, name: `[${k}]`, type: 'int', addr: `0xb0${(k * 4).toString(16)}`, value });
const oldBuf = (freed) => [old(0, '10', freed), old(1, '20', freed), old(2, '30', freed)];
const newBuf = [neu(0, '5'), neu(1, '10'), neu(2, '20'), neu(3, '30')];

export default {
	regions: { stack: '변수', heap: '원소 버퍼(자유 공간)' },
	code: `std::vector<int> v{ 10, 20, 30 };
auto it{ v.begin() + 1 };
v.insert(v.begin(), 5);
// std::println("{}", *it);  // 위험
it = v.begin() + 2;
std::println("{}", *it);     // 20`,
	steps: [
		{
			line: 1,
			note: 'v가 원소 셋을 담은 버퍼를 가짐. 원소는 연속된 메모리에 있고, 용량도 3이라고 하자',
			stack: [v('o0')],
			heap: oldBuf(false),
		},
		{
			line: 2,
			note: 'it는 두 번째 원소 20을 참조함',
			stack: [v('o0'), it('o1')],
			heap: oldBuf(false),
		},
		{
			line: 3,
			note: '맨 앞에 넣으려면 원소가 넷이 되어야 하는데 용량이 3. vector가 더 큰 새 버퍼를 잡고 원소를 옮긴 뒤 옛 버퍼를 해제함',
			stack: [v('n0'), it('o1')],
			heap: [...oldBuf(true), ...newBuf],
		},
		{
			line: 4,
			note: 'it는 여전히 해제된 옛 버퍼를 가리킴. 이것을 역참조하면 정의되지 않은 동작. 반복자는 원소를 따라 "알아서" 옮겨 가지 않음',
			stack: [v('n0'), it('o1')],
			heap: [...oldBuf(true), ...newBuf],
		},
		{
			line: 5,
			note: '넣거나 지운 뒤에는 반복자를 다시 얻음. 20은 이제 위치 2에 있음',
			stack: [v('n0'), it('n2')],
			heap: newBuf,
			output: '',
		},
		{
			line: 6,
			note: '새 반복자로 안전하게 읽음',
			stack: [v('n0'), it('n2')],
			heap: newBuf,
			output: '20',
		},
	],
};
