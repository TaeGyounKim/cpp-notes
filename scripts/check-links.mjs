// 글에 달린 cppreference 링크(<CppRef path="..." />)가 실제로 열리는지 확인한다.
// 사용법: node scripts/check-links.mjs <파일.mdx ...>
import { readFile } from 'node:fs/promises';

const files = process.argv.slice(2);
const paths = new Set();
for (const file of files) {
	const text = await readFile(file, 'utf8');
	for (const m of text.matchAll(/<CppRef path="([^"]+)"/g)) paths.add(m[1]);
}

const pages = new Map();
let failed = false;
for (const path of [...paths].sort()) {
	const [page, anchor] = path.split('#');
	if (!pages.has(page)) {
		const res = await fetch(`https://en.cppreference.com/w/${page}`, { headers: { 'User-Agent': 'Mozilla/5.0' } });
		pages.set(page, { status: res.status, html: res.ok ? await res.text() : '' });
	}
	const { status, html } = pages.get(page);
	const anchorOk = !anchor || html.includes(`id="${anchor}"`);
	if (status !== 200 || !anchorOk) {
		failed = true;
		console.log(`실패 ${status}${anchorOk ? '' : ' (앵커 없음)'}  ${path}`);
	}
}
console.log(`${paths.size}개 확인, ${failed ? '실패 있음' : '모두 열림'}`);
if (failed) process.exitCode = 1;
