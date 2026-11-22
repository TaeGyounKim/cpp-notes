// "shared_ptr와 weak_ptr" 글의 시각화: 참조 횟수가 늘고 줄다가 0이 되는 순간.
// 주소는 설명을 위해 지어낸 값이다. 실제 shared_ptr는 객체와 제어 블록을 함께 가리키지만,
// 여기서는 객체를 가리키는 화살표만 그리고 참조 횟수는 따로 보여 준다.

const a = (extra) => ({ id: 'a', name: 'a', type: 'shared_ptr<Song>', addr: '0x100', ...extra });
const b = (extra) => ({ id: 'b', name: 'b', type: 'shared_ptr<Song>', addr: '0x108', ...extra });
const w = (extra) => ({ id: 'w', name: 'w', type: 'weak_ptr<Song>', addr: '0x110', ...extra });
const count = (use, weak, freed) => ({
	id: 'cb',
	name: '제어 블록',
	type: 'use / weak',
	addr: '0x990',
	value: `${use} / ${weak}`,
	freed,
});
const song = (freed) => ({ id: 's', type: 'Song', addr: '0x9a0', value: '"Intro"', freed });

export default {
	code: `auto a{ std::make_shared<Song>("Intro") };
auto b{ a };
std::weak_ptr<Song> w{ a };
a.reset();
b.reset();
auto c{ w.lock() };   // 빈 shared_ptr`,
	steps: [
		{
			line: 1,
			note: 'make_shared가 Song과 함께 "제어 블록"을 만듦. 제어 블록에는 주인의 수(use)와 지켜보는 weak_ptr의 수(weak)가 적힘. 주인은 a 하나',
			stack: [a({ pointsTo: 's' })],
			heap: [count(1, 0), song()],
		},
		{
			line: 2,
			note: 'shared_ptr를 복사하면 같은 객체를 가리키는 주인이 하나 늘고, use가 2가 됨. 객체는 여전히 하나',
			stack: [a({ pointsTo: 's' }), b({ pointsTo: 's' })],
			heap: [count(2, 0), song()],
		},
		{
			line: 3,
			note: 'weak_ptr는 지켜보기만 함. 주인의 수(use)는 그대로 2이고 weak만 1이 됨',
			stack: [a({ pointsTo: 's' }), b({ pointsTo: 's' }), w({ pointsTo: 's' })],
			heap: [count(2, 1), song()],
		},
		{
			line: 4,
			note: 'a가 손을 뗌. use가 1로 줄었지만 0이 아니므로 Song은 살아 있음',
			stack: [a({ value: 'nullptr' }), b({ pointsTo: 's' }), w({ pointsTo: 's' })],
			heap: [count(1, 1), song()],
		},
		{
			line: 5,
			note: '마지막 주인 b가 손을 떼어 use가 0. 바로 이 순간 Song이 지워짐. weak_ptr가 지켜보고 있어도 막지 못함',
			stack: [a({ value: 'nullptr' }), b({ value: 'nullptr' }), w({ pointsTo: 's' })],
			heap: [count(0, 1), song(true)],
		},
		{
			line: 6,
			note: 'w.lock()은 객체가 이미 사라졌으므로 빈 shared_ptr를 돌려줌. 사라진 객체를 실수로 쓰는 일이 없음. 제어 블록은 마지막 weak_ptr가 사라질 때 지워짐',
			stack: [a({ value: 'nullptr' }), b({ value: 'nullptr' }), w({ pointsTo: 's' }), { id: 'c', name: 'c', type: 'shared_ptr<Song>', addr: '0x118', value: 'nullptr' }],
			heap: [count(0, 1), song(true)],
		},
	],
};
