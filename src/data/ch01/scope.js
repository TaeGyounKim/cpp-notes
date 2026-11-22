// "클래스 첫걸음과 유니폼 초기화" 글의 시각화: 같은 이름 value가 범위마다 하나씩 있을 때.

export default {
	root: {
		label: '전역 범위',
		items: [
			{ id: 'global.value', text: 'value()' },
			{ id: 'main', text: 'main()' },
		],
		children: [
			{
				label: 'class Counter',
				items: [{ id: 'counter.value', text: 'value()' }],
			},
			{
				label: 'namespace settings',
				items: [{ id: 'settings.value', text: 'value()' }],
			},
		],
	},
	queries: [
		{
			code: 'Counter counter;\ncounter.value();',
			hits: ['counter.value'],
			ok: true,
			note: '점(.) 앞이 Counter 타입의 객체이므로 Counter 클래스 안에서 찾음',
		},
		{
			code: 'settings::value();',
			hits: ['settings.value'],
			ok: true,
			note: 'settings:: 접두어가 붙어 있으므로 settings 네임스페이스 안에서만 찾음',
		},
		{
			code: '::value();',
			hits: ['global.value'],
			ok: true,
			note: '이름 없이 ::만 붙이면 전역 범위를 뜻함',
		},
		{
			code: 'value();',
			hits: ['global.value'],
			ok: true,
			note: '접두어가 없으면 지금 있는 범위(main)부터 바깥으로 찾아 나감. main 안에는 없고, 그 바깥인 전역 범위에서 찾음',
		},
		{
			code: 'using namespace settings;\nvalue();',
			hits: ['global.value', 'settings.value'],
			ok: false,
			note: 'using 지시문 때문에 settings의 value도 함께 보임. 둘 가운데 어느 것인지 정할 수 없어 오류',
		},
	],
};
