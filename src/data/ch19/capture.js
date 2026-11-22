// "std::function과 람다 표현식" 글의 시각화: 값으로 캡처하면 클로저 안에 복사본이,
// 참조로 캡처하면 원본을 가리키는 참조가 생긴다. 주소는 설명을 위해 지어낸 값이다.

const limit = (v) => ({ id: 'limit', name: 'limit', type: 'int', addr: '0x7f0', value: v });
const count = (v) => ({ id: 'count', name: 'count', type: 'int', addr: '0x7ec', value: v });
const byVal = (v) => ({ id: 'byVal', name: 'byValue (클로저)', type: 'int limit 복사본', addr: '0x7e0', value: v });
const byRef = () => ({ id: 'byRef', name: 'byRef (클로저)', type: 'int& count', addr: '0x7d8', pointsTo: 'count' });

export default {
	code: `int limit{ 25 };
int count{ 0 };
auto byValue{ [limit](int t) { return t > limit; } };
auto byRef{ [&count] { ++count; } };
limit = 30;
byRef();
bool hot{ byValue(28) };   // true`,
	steps: [
		{ line: 1, note: '지역 변수 limit', stack: [limit('25')] },
		{ line: 2, note: '지역 변수 count', stack: [limit('25'), count('0')] },
		{
			line: 3,
			note: '[limit]: 값으로 캡처. 컴파일러가 만든 클로저 객체 안에 limit의 복사본(25)이 데이터 멤버로 들어감',
			stack: [limit('25'), count('0'), byVal('25')],
		},
		{
			line: 4,
			note: '[&count]: 참조로 캡처. 클로저 안의 데이터 멤버는 count를 가리키는 참조',
			stack: [limit('25'), count('0'), byVal('25'), byRef()],
		},
		{
			line: 5,
			note: '원본 limit을 30으로 바꿔도 byValue 안의 복사본은 25 그대로',
			stack: [limit('30'), count('0'), byVal('25'), byRef()],
		},
		{
			line: 6,
			note: 'byRef()를 부르면 참조를 통해 원본 count가 1이 됨',
			stack: [limit('30'), count('1'), byVal('25'), byRef()],
		},
		{
			line: 7,
			note: 'byValue(28)은 복사본 25와 비교하므로 true. 원본 30과 비교했다면 false였을 것',
			stack: [limit('30'), count('1'), byVal('25'), byRef()],
		},
	],
};
