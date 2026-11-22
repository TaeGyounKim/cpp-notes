// "unique_ptr" 글의 시각화: 소유권이 하나뿐이라는 것, move로 넘기기, 범위를 벗어나며 지우기.
// 주소는 설명을 위해 지어낸 값이다.

const a = (extra) => ({ id: 'a', name: 'a', type: 'unique_ptr<Song>', addr: '0x100', ...extra });
const b = (extra) => ({ id: 'b', name: 'b', type: 'unique_ptr<Song>', addr: '0x108', ...extra });
const song = (value, freed) => ({ id: 's', type: 'Song', addr: '0x9a0', value, freed });

export default {
	code: `{
    auto a{ std::make_unique<Song>("Intro") };
    // auto b{ a };   // 복사: 컴파일 오류
    auto b{ std::move(a) };
    b.reset(new Song{ "Verse" });
}`,
	steps: [
		{
			line: 2,
			note: 'make_unique가 자유 저장소에 Song을 만들고, 그 주소를 a가 홀로 가짐(소유)',
			stack: [a({ pointsTo: 's' })],
			heap: [song('"Intro"')],
		},
		{
			line: 3,
			note: '복사하면 소유자가 둘이 되어 같은 객체를 두 번 지우게 됨. 그래서 unique_ptr은 복사를 막아 둠(컴파일 오류)',
			stack: [a({ pointsTo: 's' })],
			heap: [song('"Intro"')],
		},
		{
			line: 4,
			note: 'std::move로 소유권을 b에게 넘김. Song은 그대로 같은 자리에 있고, a는 nullptr이 됨. 소유자는 여전히 하나',
			stack: [a({ value: 'nullptr' }), b({ pointsTo: 's' })],
			heap: [song('"Intro"')],
		},
		{
			line: 5,
			note: 'reset에 새 객체를 주면, 먼저 가지고 있던 Intro를 지우고 새 Verse를 가짐',
			stack: [a({ value: 'nullptr' }), b({ pointsTo: 's2' })],
			heap: [song('"Intro"', true), { id: 's2', type: 'Song', addr: '0x9c0', value: '"Verse"' }],
		},
		{
			line: 6,
			note: '범위가 끝나 b가 사라지면서 소멸자가 Verse를 지움. a는 비어 있으므로 지울 것이 없음. delete를 한 번도 적지 않았지만 남은 것이 없음',
			stack: [],
			heap: [song('"Intro"', true), { id: 's2', type: 'Song', addr: '0x9c0', value: '"Verse"', freed: true }],
		},
	],
};
