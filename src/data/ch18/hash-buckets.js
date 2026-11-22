// "해시 테이블과 평평한 연관 컨테이너" 글의 시각화: 해시 값으로 버킷을 고르고,
// 같은 버킷에 떨어진 키는 연결 리스트로 잇는다(선형 체이닝).
// 버킷 번호와 주소는 설명을 위해 지어낸 값이며, 실제 구현의 세부는 다를 수 있다.

const bucket = (k, to) => ({ id: `b${k}`, name: `버킷 ${k}`, type: '버킷', pointsTo: to, value: '비었음' });
const node = (id, label, addr, to) => ({ id, name: label, type: '노드(키, 값, 다음)', addr, pointsTo: to, value: 'nullptr' });

const living = (to) => node('n1', '거실 22', '0x9a0', to);
const kitchen = node('n2', '부엌 25', '0x9c0');
const bedroom = node('n3', '침실 19', '0x9e0');

export default {
	regions: { stack: '버킷 배열', heap: '노드(자유 공간)' },
	code: `std::unordered_map<std::string, int> temps;
temps["거실"] = 22;   // 해시 → 버킷 2
temps["부엌"] = 25;   // 해시 → 버킷 0
temps["침실"] = 19;   // 해시 → 버킷 2
int t{ temps["침실"] };`,
	steps: [
		{
			line: 1,
			note: '해시 테이블은 버킷의 배열. 여기서는 버킷 넷으로 시작한다고 하자. 모두 비어 있음. 노드 칸에는 키와 값을 적고, 오른쪽에 다음 노드의 주소를 적음',
			stack: [bucket(0), bucket(1), bucket(2), bucket(3)],
		},
		{
			line: 2,
			note: '키 "거실"을 해시 함수에 넣어 해시 값을 얻고, 그것을 버킷 수로 나눈 나머지(예: 2)를 버킷 번호로 씀. 버킷 2가 새 노드를 가리킴',
			stack: [bucket(0), bucket(1), bucket(2, 'n1'), bucket(3)],
			heap: [living()],
		},
		{
			line: 3,
			note: '"부엌"은 버킷 0으로. 정렬하지 않으므로 원소의 순서는 해시 값이 정함',
			stack: [bucket(0, 'n2'), bucket(1), bucket(2, 'n1'), bucket(3)],
			heap: [living(), kitchen],
		},
		{
			line: 4,
			note: '"침실"도 버킷 2에 떨어짐: 충돌. 같은 버킷의 원소들을 연결 리스트로 이음(선형 체이닝). "거실" 노드의 다음이 "침실"',
			stack: [bucket(0, 'n2'), bucket(1), bucket(2, 'n1'), bucket(3)],
			heap: [living('n3'), kitchen, bedroom],
		},
		{
			line: 5,
			note: '찾기: "침실"을 해시해 버킷 2로 바로 감(상수 시간). 그 버킷의 리스트에서 키를 ==로 비교: "거실"은 아니고 "침실"이 맞음. 충돌이 적을수록 비교가 적어 빠름',
			stack: [bucket(0, 'n2'), bucket(1), bucket(2, 'n1'), bucket(3)],
			heap: [living('n3'), kitchen, bedroom],
		},
	],
};
