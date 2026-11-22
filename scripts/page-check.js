async () => {
	// 페이지 전체를 점검한다: 깨진 스타일 주입, 편집기, 넘치는 표/코드, 시각화 단계 전부 넘기기.
	const wait = (ms) => new Promise((r) => setTimeout(r, ms));
	await wait(2500);
	const rawStyles = [...document.querySelectorAll('style')].filter((s) => /^\s*<script/.test(s.textContent)).length;
	const main = document.querySelector('main');
	const mainWidth = main.clientWidth;
	const overflow = [];
	for (const el of main.querySelectorAll('table, pre, .expressive-code, .flow, svg')) {
		const r = el.getBoundingClientRect();
		if (r.width > mainWidth + 2) overflow.push(el.tagName + ':' + Math.round(r.width));
	}
	const scrollTables = [...main.querySelectorAll('table')].filter((t) => t.scrollWidth > t.clientWidth + 2).length;
	// 시각화: 모든 단계를 넘기며 코드 영역에 가로 스크롤이 생기는지 본다.
	const viz = [];
	const nextButtons = [...document.querySelectorAll('button')].filter((b) => b.textContent.includes('다음'));
	for (const btn of nextButtons) {
		let steps = 1;
		let codeScroll = false;
		const root = btn.closest('astro-island') || btn.parentElement.parentElement;
		const check = () => {
			for (const el of root.querySelectorAll('pre, .code, code')) {
				if (el.scrollWidth > el.clientWidth + 2) codeScroll = true;
			}
		};
		check();
		while (!btn.disabled && steps < 60) {
			btn.click();
			await wait(120);
			steps++;
			check();
		}
		viz.push({ steps, codeScroll });
	}
	const editorScroll = [...document.querySelectorAll('.cm-scroller')].map((e, i) => (e.scrollWidth > e.clientWidth + 2 ? i + 1 : 0)).filter(Boolean);
	// 정적 코드 블록(실행 편집기·시각화 밖)이 가로로 스크롤되는지
	const preScroll = [...main.querySelectorAll('pre')]
		.filter((p) => !p.closest('astro-island') && p.scrollWidth > p.clientWidth + 2)
		.map((p) => p.textContent.split('\n').find((l) => l.length > 60)?.slice(0, 40) ?? '?');
	const missingGlyph = [...main.querySelectorAll('td, li, p')].filter((e) => /[⁰¹²³⁴⁵⁶⁷⁸⁹⁻₩]/.test(e.textContent)).length;
	return {
		title: document.title,
		rawStyles,
		editors: document.querySelectorAll('.cm-editor').length,
		fallbacks: document.querySelectorAll('pre.fallback').length,
		unhydrated: document.querySelectorAll('astro-island[ssr]').length,
		cppref: document.querySelectorAll('a.cppref').length,
		overflow,
		scrollTables,
		viz,
		editorScroll,
		preScroll,
		missingGlyph,
		height: document.documentElement.scrollHeight,
	};
}
