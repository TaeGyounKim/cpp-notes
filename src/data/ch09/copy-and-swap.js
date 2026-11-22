// "깊은 복사와 복사 후 교환" 글의 시각화: a = b;를 복사 후 교환으로 처리하는 세 단계.
// 주소는 설명을 위해 지어낸 값이다. 너비·높이 멤버는 생략하고 m_cells만 그린다.

const a = (extra) => ({ id: 'a', name: 'a.m_cells', type: 'double*', addr: '0x100', ...extra });
const b = (extra) => ({ id: 'b', name: 'b.m_cells', type: 'double*', addr: '0x0e0', ...extra });
const temp = (extra) => ({ id: 't', name: 'temp.m_cells', type: 'double*', addr: '0x0a0', ...extra });
const oldA = (freed) => ({ id: 'ha', name: 'a의 원래 2칸', type: 'double[2]', addr: '0x9a0', freed });
const arrB = { id: 'hb', name: 'b의 6칸', type: 'double[6]', addr: '0x9c0' };
const copy = { id: 'hc', name: '6칸 사본', type: 'double[6]', addr: '0x9f0' };

export default {
	code: `Grid& operator=(const Grid& rhs)
{
    Grid temp{ rhs };
    swap(temp);
    return *this;
}
// 부르는 쪽: a = b;`,
	steps: [
		{
			line: 7,
			note: 'a = b;를 부르기 직전. a는 2칸, b는 6칸 배열을 가짐. 함수 안에서 *this는 a, rhs는 b',
			stack: [a({ pointsTo: 'ha' }), b({ pointsTo: 'hb' })],
			heap: [oldA(), arrB],
		},
		{
			line: 3,
			note: '1단계: rhs(b)의 깊은 사본 temp를 만듦. 새 배열을 잡고 값을 복사함. 여기서 예외가 나도 a는 아직 손대지 않았으므로 그대로',
			stack: [a({ pointsTo: 'ha' }), b({ pointsTo: 'hb' }), temp({ pointsTo: 'hc' })],
			heap: [oldA(), arrB, copy],
		},
		{
			line: 4,
			note: '2단계: a와 temp의 멤버를 맞바꿈. 포인터 두 개와 크기 값만 바꾸므로 예외가 날 일이 없음. 이제 a가 사본을, temp가 a의 원래 배열을 가짐',
			stack: [a({ pointsTo: 'hc' }), b({ pointsTo: 'hb' }), temp({ pointsTo: 'ha' })],
			heap: [oldA(), arrB, copy],
		},
		{
			line: 6,
			note: '3단계: 함수가 끝나며 temp가 소멸함. temp의 소멸자가 지우는 것은 a의 원래 배열. 누수도, 공유도 없음',
			stack: [a({ pointsTo: 'hc' }), b({ pointsTo: 'hb' })],
			heap: [oldA(true), arrB, copy],
		},
	],
};
