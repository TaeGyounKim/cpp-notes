// "다시 던지기, 스택 풀기와 정리" 글의 시각화: 스택 풀기는 지역 객체의 소멸자를 부르지만,
// 날 포인터가 가리키던 힙 객체는 지우지 않는다. 주소는 설명을 위해 지어낸 값이다.

const a = { id: 'a', name: 'a', type: 'T', addr: '0x7f0', value: '살아 있음' };
const u = { id: 'u', name: 'u', type: 'unique_ptr<T>', addr: '0x7e8' };
const p = { id: 'p', name: 'p', type: 'T*', addr: '0x7e0' };
const hu = { id: 'hu', name: 'u가 가진 T', type: 'T', addr: '0x9a0' };
const hp = { id: 'hp', name: 'new T', type: 'T', addr: '0x9c0' };

export default {
	code: `void middle()
{
    T a;
    auto u{ std::make_unique<T>() };
    T* p{ new T };
    inner();    // 예외를 던짐
    delete p;
}`,
	steps: [
		{
			line: 3,
			note: '스택에 지역 객체 a를 만듦',
			stack: [a],
		},
		{
			line: 4,
			note: '스마트 포인터 u가 힙의 T를 가짐. u가 소멸하면 그 T도 지워짐',
			stack: [a, { ...u, pointsTo: 'hu' }],
			heap: [hu],
		},
		{
			line: 5,
			note: '날 포인터 p가 힙의 T를 가리킴. 지우려면 delete p가 실행되어야 함',
			stack: [a, { ...u, pointsTo: 'hu' }, { ...p, pointsTo: 'hp' }],
			heap: [hu, hp],
		},
		{
			line: 6,
			note: 'inner()가 예외를 던짐. middle()에는 처리기가 없으므로 이 프레임이 풀림. 7번 줄 delete p는 실행되지 않음',
			stack: [a, { ...u, pointsTo: 'hu' }, { ...p, pointsTo: 'hp' }],
			heap: [hu, hp],
		},
		{
			line: 8,
			note: '스택 풀기: 지역 객체를 만든 반대 순서로 소멸자를 부름. u의 소멸자가 힙의 T를 지움. a도 소멸함. p는 포인터일 뿐이라 사라지기만 하고, 가리키던 T는 아무도 지우지 않음',
			stack: [
				{ ...a, freed: true },
				{ ...u, freed: true },
				{ ...p, freed: true },
			],
			heap: [{ ...hu, freed: true }, { ...hp, value: '누수' }],
		},
		{
			line: 8,
			note: '프레임이 사라진 뒤: 힙에 new T가 남았지만 가리키는 포인터가 없어 다시는 지울 수 없음(메모리 누수). 날 포인터 대신 스마트 포인터나 스택 객체를 쓰면 이런 일이 없음',
			stack: [],
			heap: [{ ...hp, value: '누수' }],
		},
	],
};
