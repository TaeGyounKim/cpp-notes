// "바꾸는 알고리즘" 글의 시각화: std::remove는 지우지 않고 남길 원소를 앞으로 옮긴다.
// 읽는 위치(read)와 쓰는 위치(write) 두 반복자로 설명한다. 실제 구현의 세부는 다를 수 있고,
// 끝부분의 남은 값은 GCC로 실행했을 때의 값이다(표준은 정하지 않음).

const cell = (k, value, extra) => ({ id: `e${k}`, name: `v[${k}]`, type: 'int', value, ...extra });
const vec = (vals, extra = {}) => vals.map((v, k) => cell(k, v, extra[k]));
const read = (k) => ({ id: 'read', name: 'read', type: '읽는 위치', pointsTo: `e${k}` });
const write = (k) => ({ id: 'write', name: 'write', type: '쓸 위치', pointsTo: `e${k}` });
const endIt = () => ({ id: 'end', name: 'end()', type: '끝', value: 'v[6]' });

export default {
	regions: { stack: '반복자', heap: 'vector의 원소' },
	code: `std::vector v{ 3, 0, 5, 0, 0, 7 };
auto it{ std::remove(v.begin(), v.end(), 0) };
v.erase(it, v.end());`,
	steps: [
		{
			line: 1,
			note: '원소 여섯. 이 중 0을 모두 없애고 싶음',
			stack: [endIt()],
			heap: vec([3, 0, 5, 0, 0, 7]),
		},
		{
			line: 2,
			note: 'remove 시작: read와 write가 모두 맨 앞. v[0]=3은 남길 원소이고 이미 제자리이므로 둘 다 한 칸 나아감',
			stack: [read(0), write(0), endIt()],
			heap: vec([3, 0, 5, 0, 0, 7]),
		},
		{
			line: 2,
			note: 'v[1]=0은 지울 원소: write는 그대로 두고 read만 나아감',
			stack: [read(1), write(1), endIt()],
			heap: vec([3, 0, 5, 0, 0, 7]),
		},
		{
			line: 2,
			note: 'v[2]=5는 남길 원소: write 자리(v[1])로 옮기고(이동 대입) 둘 다 나아감',
			stack: [read(2), write(1), endIt()],
			heap: vec([3, 5, 5, 0, 0, 7]),
		},
		{
			line: 2,
			note: 'v[3], v[4]는 0이라 read만 지나감. v[5]=7은 남길 원소라 write 자리(v[2])로 옮김',
			stack: [read(5), write(2), endIt()],
			heap: vec([3, 5, 7, 0, 0, 7]),
		},
		{
			line: 2,
			note: 'remove는 write 위치(v[3])를 돌려줌. 앞쪽 [0, 3)이 남길 원소이고, 뒤쪽은 쓰지 말아야 할 찌꺼기. 크기는 아직 6!',
			stack: [{ id: 'it', name: 'it', type: 'remove의 결과', pointsTo: 'e3' }, endIt()],
			heap: vec([3, 5, 7, 0, 0, 7], { 3: { value: '찌꺼기' }, 4: { value: '찌꺼기' }, 5: { value: '찌꺼기' } }),
		},
		{
			line: 3,
			note: 'erase(it, end())로 컨테이너에서 실제로 지움. 이제 크기 3. 두 번째 인수 end()를 빼먹으면 it 원소 하나만 지워짐',
			stack: [],
			heap: [
				...vec([3, 5, 7]),
				cell(3, '찌꺼기', { freed: true }),
				cell(4, '찌꺼기', { freed: true }),
				cell(5, '찌꺼기', { freed: true }),
			],
		},
	],
};
