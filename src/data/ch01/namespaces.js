// "네임스페이스" 글의 시각화: 같은 이름 play가 어느 것을 가리키게 되는가.

export default {
	root: {
		label: '전역 네임스페이스',
		items: [{ id: 'main', text: 'main()' }],
		children: [
			{
				label: 'namespace audio',
				items: [
					{ id: 'audio.play', text: 'play()' },
					{ id: 'audio.stop', text: 'stop()' },
				],
			},
			{
				label: 'namespace video',
				items: [{ id: 'video.play', text: 'play()' }],
			},
		],
	},
	queries: [
		{
			code: 'audio::play();',
			hits: ['audio.play'],
			ok: true,
			note: 'audio:: 접두어가 붙어 있으므로 audio 안에서만 찾음',
		},
		{
			code: 'video::play();',
			hits: ['video.play'],
			ok: true,
			note: '이름은 같지만 video:: 접두어가 붙어 있으므로 video 안의 것을 찾음',
		},
		{
			code: 'play();',
			hits: [],
			ok: false,
			note: '접두어가 없으면 지금 있는 곳(전역)에서만 찾음. 전역에는 play가 없으므로 오류',
		},
		{
			code: 'using namespace audio;\nplay();',
			hits: ['audio.play'],
			ok: true,
			note: 'using 지시문이 audio의 이름을 전부 보이게 만듦. 접두어 없이도 audio의 play를 찾음',
		},
		{
			code: 'using namespace audio;\nusing namespace video;\nplay();',
			hits: ['audio.play', 'video.play'],
			ok: false,
			note: '두 네임스페이스의 play가 모두 보여서 어느 것인지 정할 수 없음. 모호하다는 오류',
		},
		{
			code: 'using namespace audio;\nusing namespace video;\nvideo::play();',
			hits: ['video.play'],
			ok: true,
			note: '둘 다 보이는 상황에서도 접두어를 붙이면 모호함이 사라짐',
		},
		{
			code: 'using audio::play;\nstop();',
			hits: [],
			ok: false,
			note: 'using 선언은 play 하나만 보이게 만듦. stop은 여전히 audio::stop이라고 써야 함',
		},
	],
};
