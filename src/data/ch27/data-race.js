// "멀티스레딩 개념" 글의 시각화: 공유 변수 value를 스레드 1은 1 늘리고 스레드 2는 1 줄인다.
// 각 연산은 "읽기 → 계산 → 쓰기" 세 단계이고, 두 스레드의 단계가 섞이면 갱신 하나가 사라진다.
// (실제 기계어와 순서는 하드웨어·컴파일러에 따라 다르다. 여기서는 개념만 보인다.)

const reg = (t, v) => ({ id: `r${t}`, name: `r${t}`, type: `스레드 ${t}의 레지스터`, value: v });
const shared = (v, extra = {}) => ({ id: 'value', name: 'value', type: '공유 변수', value: String(v), ...extra });

export default {
	regions: { stack: '스레드마다 따로 가진 레지스터', heap: '두 스레드가 함께 보는 메모리' },
	code: `T1: r1 = value
T2: r2 = value
T1: r1 = r1 + 1
T2: r2 = r2 - 1
T2: value = r2
T1: value = r1`,
	steps: [
		{ line: 1, note: 'T1은 스레드 1, T2는 스레드 2. 처음 value는 1. 스레드 1이 value를 자기 레지스터 r1로 읽음', stack: [reg(1, '1'), reg(2, '?')], heap: [shared(1)] },
		{ line: 2, note: '스레드 1이 아직 쓰기 전에 스레드 2도 value를 읽음. 둘 다 1을 봄', stack: [reg(1, '1'), reg(2, '1')], heap: [shared(1)] },
		{ line: 3, note: '스레드 1이 r1을 2로 계산. 아직 메모리에는 쓰지 않음', stack: [reg(1, '2'), reg(2, '1')], heap: [shared(1)] },
		{ line: 4, note: '스레드 2가 r2를 0으로 계산', stack: [reg(1, '2'), reg(2, '0')], heap: [shared(1)] },
		{ line: 5, note: '스레드 2가 value에 0을 씀', stack: [reg(1, '2'), reg(2, '0')], heap: [shared(0)] },
		{ line: 6, note: '스레드 1이 value에 2를 씀. 스레드 2의 감소가 덮여 사라짐. 차례대로 했다면 1이어야 함', stack: [reg(1, '2'), reg(2, '0')], heap: [shared(2)] },
	],
};
