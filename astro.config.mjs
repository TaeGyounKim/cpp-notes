// @ts-check
import { defineConfig } from 'astro/config';
import starlight from '@astrojs/starlight';
import starlightSidebarTopics from 'starlight-sidebar-topics';
import svelte from '@astrojs/svelte';

// GitHub Pages에서는 https://taegyounkim.github.io/cpp-notes/ 아래에 놓인다.
// 로컬(npm run dev)에서는 주소 맨 앞(/)에 그대로 둔다.
const onPages = process.env.GITHUB_ACTIONS === 'true';

// 장 하나 = 왼쪽 메뉴의 그룹 하나. 폴더 안의 글이 자동으로 들어간다.
const chapter = (label, directory) => ({ label, items: [{ autogenerate: { directory } }] });

// 상단 탭. 첫 탭은 안내 글이고, 그 뒤로 Part가 내용이 생기는 대로 하나씩 추가된다.
const parts = [
	{
		label: '시작하기',
		link: '/guide/how-to-use/',
		items: [{ label: '시작하기', items: [{ autogenerate: { directory: 'guide' } }] }],
	},
	{
		label: 'Part 1 · C++ 입문',
		link: '/part1/ch01/01-hello-world/',
		items: [
			chapter('1장. C++와 표준 라이브러리 속성 코스', 'part1/ch01'),
			chapter('2장. 문자열과 문자열 뷰', 'part1/ch02'),
			chapter('3장. 스타일을 살려 코딩하기', 'part1/ch03'),
		],
	},
	{
		label: 'Part 2 · 소프트웨어 설계',
		link: '/part2/ch04/01-what-is-design/',
		items: [
			chapter('4장. 전문가다운 C++ 프로그램 설계', 'part2/ch04'),
			chapter('5장. 클래스로 설계하기', 'part2/ch05'),
		],
	},
];

export default defineConfig({
	site: onPages ? 'https://taegyounkim.github.io' : undefined,
	base: onPages ? '/cpp-notes' : undefined,
	devToolbar: { enabled: false },
	integrations: [
		starlight({
			title: 'C++ 스터디',
			defaultLocale: 'root',
			locales: { root: { label: '한국어', lang: 'ko' } },
			plugins: [starlightSidebarTopics(parts)],
			components: {
				Header: './src/components/Header.astro',
				Sidebar: './src/components/Sidebar.astro',
			},
			customCss: ['./src/styles/palette.css', './src/styles/typography.css', './src/styles/part-tabs.css'],
		}),
		svelte(),
	],
});
