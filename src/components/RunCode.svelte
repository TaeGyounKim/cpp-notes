<script>
	/*
	 * 페이지 안에서 고치고 실행하는 코드 블록.
	 * 컴파일과 실행은 Compiler Explorer(godbolt.org) 공개 API에 맡긴다.
	 */
	import { onMount } from 'svelte';
	import { EditorView, basicSetup } from 'codemirror';
	import { keymap } from '@codemirror/view';
	import { indentWithTab } from '@codemirror/commands';
	import { cpp } from '@codemirror/lang-cpp';
	import { HighlightStyle, indentUnit, syntaxHighlighting } from '@codemirror/language';
	import { tags as t } from '@lezer/highlight';

	let {
		code,
		compiler = 'g162',
		compilerName = 'GCC 16.2',
		flags = '-std=c++23 -Wall -Wextra',
		// 키보드 입력(std::cin)으로 넘길 값. 지정하면 입력 칸이 나타난다.
		stdin = undefined,
	} = $props();

	let host;
	let view;
	let current = $state(code);
	let input = $state(stdin ?? '');
	let status = $state('idle'); // idle | running | done | failed
	let result = $state(null);
	let mounted = $state(false);

	const stripAnsi = (s) => s.replace(/\x1b\[[0-9;]*[A-Za-z]/g, '');
	const text = (rows) => stripAnsi((rows ?? []).map((r) => r.text).join('\n'));

	// 실행이 막혔을 때도 쓸 수 있도록, 같은 코드를 Compiler Explorer에서 여는 링크.
	const link = $derived.by(() => {
		const state = {
			sessions: [
				{ id: 1, language: 'c++', source: current, compilers: [], executors: [{ compiler: { id: compiler, options: flags } }] },
			],
		};
		const bytes = new TextEncoder().encode(JSON.stringify(state));
		const b64 = btoa(String.fromCharCode(...bytes));
		return `https://godbolt.org/clientstate/${encodeURIComponent(b64)}`;
	});

	async function run() {
		if (status === 'running') return true;
		status = 'running';
		result = null;
		try {
			const res = await fetch(`https://godbolt.org/api/compiler/${compiler}/compile`, {
				method: 'POST',
				headers: { 'Content-Type': 'application/json', Accept: 'application/json' },
				signal: AbortSignal.timeout(30000),
				body: JSON.stringify({
					source: view.state.doc.toString(),
					lang: 'c++',
					allowStoreCodeDebug: false,
					options: {
						userArguments: flags,
						executeParameters: { args: [], stdin: stdin === undefined ? '' : input + String.fromCharCode(10) },
						compilerOptions: { executorRequest: true },
						filters: { execute: true },
						tools: [],
						libraries: [],
					},
				}),
			});
			if (res.status === 429) throw new Error('요청이 몰려 잠시 제한되었습니다. 1분쯤 뒤에 다시 실행해 보세요');
			if (!res.ok) throw new Error(`HTTP ${res.status}`);
			const d = await res.json();
			result = {
				built: d.didExecute,
				compiler: text(d.buildResult?.stderr),
				stdout: text(d.stdout),
				stderr: text(d.stderr),
				exit: d.code,
			};
			status = 'done';
		} catch (e) {
			result = { error: e.name === 'TimeoutError' ? '응답 시간이 초과되었습니다.' : String(e.message ?? e) };
			status = 'failed';
		}
		return true;
	}

	function reset() {
		view.dispatch({ changes: { from: 0, to: view.state.doc.length, insert: code } });
		result = null;
		status = 'idle';
	}

	const highlight = HighlightStyle.define([
		{ tag: [t.keyword, t.controlKeyword, t.modifier], color: 'var(--run-kw)' },
		{ tag: [t.typeName, t.standard(t.typeName), t.namespace], color: 'var(--run-type)' },
		{ tag: [t.string, t.character, t.processingInstruction], color: 'var(--run-str)' },
		{ tag: [t.number, t.bool, t.null], color: 'var(--run-num)' },
		{ tag: [t.comment], color: 'var(--run-comment)', fontStyle: 'italic' },
	]);

	const theme = EditorView.theme({
		'&': { fontSize: 'var(--sl-text-code)', backgroundColor: 'transparent', color: 'var(--sl-color-white)' },
		'.cm-content': { fontFamily: 'var(--__sl-font-mono)', caretColor: 'var(--sl-color-white)' },
		'.cm-gutters': { backgroundColor: 'transparent', color: 'var(--sl-color-gray-4)', border: 'none' },
		'.cm-activeLine, .cm-activeLineGutter': { backgroundColor: 'var(--sl-color-gray-6)' },
		'.cm-cursor': { borderLeftColor: 'var(--sl-color-white)' },
		'&.cm-focused': { outline: 'none' },
		'&.cm-focused .cm-selectionBackground, .cm-selectionBackground': { backgroundColor: 'var(--sl-color-accent-low)' },
	});

	onMount(() => {
		mounted = true;
		view = new EditorView({
			parent: host,
			doc: code,
			extensions: [
				keymap.of([{ key: 'Mod-Enter', run }, indentWithTab]),
				indentUnit.of('    '),
				basicSetup,
				cpp(),
				syntaxHighlighting(highlight),
				theme,
				EditorView.updateListener.of((u) => u.docChanged && (current = u.state.doc.toString())),
			],
		});
		return () => view.destroy();
	});
</script>

<div class="run not-content">
	<div class="editor" bind:this={host}>
		<!-- before the editor mounts, show the code as plain text -->
		{#if !mounted}<pre class="fallback">{code}</pre>{/if}
	</div>

	{#if stdin !== undefined}
		<label class="stdin">
			<span>키보드 입력</span>
			<input type="text" bind:value={input} spellcheck="false" autocomplete="off" />
		</label>
	{/if}

	<div class="bar">
		<button class="primary" onclick={run} disabled={status === 'running'}>
			{status === 'running' ? '실행 중…' : '▶ 실행'}
		</button>
		<button onclick={reset} disabled={current === code && !result}>원래대로</button>
		<span class="meta">{compilerName} · {flags} · Ctrl+Enter</span>
		<a href={link} target="_blank" rel="noopener">Compiler Explorer에서 열기 ↗</a>
	</div>

	{#if result}
		<div class="result" aria-live="polite">
			{#if result.error}
				<p class="bad">실행 서버에 연결하지 못했습니다 ({result.error}). 위의 "Compiler Explorer에서 열기"로 실행해 보세요.</p>
			{:else}
				{#if result.compiler}
					<p class="label" class:bad={!result.built}>{result.built ? '컴파일러 경고' : '컴파일 오류'}</p>
					<pre>{result.compiler}</pre>
				{/if}
				{#if result.built}
					<p class="label">출력</p>
					<pre>{result.stdout || '(출력 없음)'}</pre>
					{#if result.stderr}
						<p class="label">표준 오류</p>
						<pre>{result.stderr}</pre>
					{/if}
					{#if result.exit !== 0}
						<p class="label bad">종료 코드 {result.exit}</p>
					{/if}
				{/if}
			{/if}
		</div>
	{/if}
</div>

<style>
	.run {
		--run-kw: var(--palette-code-keyword);
		--run-type: var(--palette-code-type);
		--run-str: var(--palette-code-string);
		--run-num: var(--palette-code-number);
		--run-comment: var(--palette-code-comment);
		margin: 1.5rem 0;
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.5rem;
		overflow: hidden;
		background: var(--sl-color-bg-nav);
		letter-spacing: 0;
	}
	.editor {
		min-height: 4rem;
		padding: 0.4rem 0;
	}
	.fallback {
		padding: 0 0.8rem 0 3rem;
		font-size: var(--sl-text-code);
		line-height: 1.4;
		white-space: pre;
		overflow-x: auto;
		border: 0;
		background: transparent;
	}
	.stdin {
		display: flex;
		align-items: center;
		gap: 0.75rem;
		padding: 0.5rem 0.8rem;
		border-top: 1px solid var(--sl-color-gray-5);
		background: var(--sl-color-bg);
		font-size: 0.8rem;
		color: var(--sl-color-gray-3);
	}
	.stdin input {
		flex: 1;
		min-width: 0;
		padding: 0.3rem 0.6rem;
		font-family: var(--__sl-font-mono);
		font-size: var(--sl-text-code);
		color: var(--sl-color-white);
		background: var(--sl-color-bg-nav);
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.3rem;
	}
	.bar {
		display: flex;
		flex-wrap: wrap;
		align-items: center;
		gap: 0.5rem 0.75rem;
		padding: 0.6rem 0.8rem;
		border-top: 1px solid var(--sl-color-gray-5);
		background: var(--sl-color-bg);
	}
	button {
		padding: 0.3rem 0.8rem;
		font: inherit;
		font-size: 0.85rem;
		color: var(--sl-color-white);
		background: transparent;
		border: 1px solid var(--sl-color-gray-4);
		border-radius: 0.3rem;
		cursor: pointer;
	}
	button.primary {
		color: var(--sl-color-black);
		background: var(--sl-color-text-accent);
		border-color: var(--sl-color-text-accent);
	}
	button:disabled {
		opacity: 0.45;
		cursor: default;
	}
	.meta {
		font-size: 0.75rem;
		color: var(--sl-color-gray-3);
	}
	a {
		margin-left: auto;
		font-size: 0.8rem;
		color: var(--sl-color-text-accent);
	}
	.result {
		padding: 0.6rem 0.8rem 0.8rem;
		border-top: 1px solid var(--sl-color-gray-5);
		background: var(--sl-color-bg);
	}
	.label {
		margin: 0.4rem 0 0.2rem;
		font-size: 0.75rem;
		font-weight: 600;
		color: var(--sl-color-gray-3);
	}
	.bad {
		color: var(--palette-error);
	}
	p.bad {
		margin: 0;
		font-size: 0.85rem;
	}
	pre {
		font-family: var(--__sl-font-mono);
		margin: 0;
		padding: 0.5rem 0.7rem;
		font-size: 0.8rem;
		line-height: 1.5;
		white-space: pre-wrap;
		overflow-wrap: anywhere;
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.3rem;
		background: var(--sl-color-bg-nav);
	}
</style>
