// 실행 예제를 사이트와 같은 조건(Compiler Explorer, GCC 16.2, -std=c++23 -Wall -Wextra)으로 실행해 본다.
// 사용법: node scripts/run-example.mjs <파일.cpp ...> [--stdin "값"] [--std c++11]
import { readFile } from 'node:fs/promises';

const args = process.argv.slice(2);
const at = args.indexOf('--stdin');
const stdin = at >= 0 ? args.splice(at, 2)[1] + '\n' : '';
const stdAt = args.indexOf('--std');
const std = stdAt >= 0 ? args.splice(stdAt, 2)[1] : 'c++23';
const text = (rows) => (rows ?? []).map((r) => r.text.replace(/\x1b\[[0-9;]*[A-Za-z]/g, '')).join('\n');

const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
const request = (source) =>
	fetch('https://godbolt.org/api/compiler/g162/compile', {
		method: 'POST',
		headers: { 'Content-Type': 'application/json', Accept: 'application/json' },
		body: JSON.stringify({
			source,
			lang: 'c++',
			allowStoreCodeDebug: false,
			options: {
				userArguments: `-std=${std} -Wall -Wextra`,
				executeParameters: { args: [], stdin },
				compilerOptions: { executorRequest: true },
				filters: { execute: true },
				tools: [],
				libraries: [],
			},
		}),
	});

let failed = false;
for (const file of args) {
	const source = await readFile(file, 'utf8');
	let res;
	// Compiler Explorer는 요청이 몰리면 잠시 제한을 건다. 간격을 두고 다시 시도한다.
	for (let attempt = 0; attempt < 5; attempt++) {
		res = await request(source);
		if (res.ok) break;
		console.error(`요청 제한(HTTP ${res.status}). 30초 뒤 다시 시도합니다.`);
		await sleep(30000);
	}
	if (!res.ok) {
		console.log(`=== ${file} [${std}] 실행 서버가 응답하지 않아 확인하지 못함`);
		failed = true;
		continue;
	}
	const d = await res.json();
	console.log(`=== ${file} [${std}] (종료 코드 ${d.code}${d.didExecute ? '' : ', 컴파일 실패'})`);
	const compiler = text(d.buildResult?.stderr);
	if (compiler) console.log(`[컴파일러]\n${compiler}`);
	if (d.didExecute) {
		console.log(text(d.stdout));
		if (d.stderr?.length) console.log(`[표준 오류]\n${text(d.stderr)}`);
	}
	if (!d.didExecute || compiler) failed = true;
	await sleep(8000);
}
process.exitCode = failed ? 1 : 0;
