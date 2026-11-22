<script>
	/*
	 * 단계별 실행 뷰어.
	 * data = {
	 *   code: string,
	 *   steps: [{
	 *     line: number,            // 방금 실행한 줄 (1부터)
	 *     note: string,            // 이 단계 설명
	 *     output?: string,         // 지금까지의 출력
	 *     stack: Cell[], heap?: Cell[]
	 *   }]
	 * }
	 * Cell = { id, name?, type, addr, value?, pointsTo?, aliases?, freed? }
	 */
	import { fade, fly } from 'svelte/transition';
	import Arrow from './StepVizArrow.svelte';

	let { data } = $props();
	const uid = $props.id();

	let i = $state(0);
	const lines = $derived(data.code.split('\n'));
	const step = $derived(data.steps[i]);
	const last = $derived(data.steps.length - 1);

	const ROW = 60;
	const CELL_H = 46;
	const TOP = 34;
	const STACK = { x: 14, w: 232 };
	const HEAP = { x: 346, w: 160 };

	const hasHeap = $derived(data.steps.some((s) => s.heap?.length));
	const width = $derived(hasHeap ? HEAP.x + HEAP.w + 14 : STACK.x + STACK.w + 90);
	const height = $derived(
		TOP + Math.max(...data.steps.map((s) => Math.max(s.stack.length, s.heap?.length ?? 0))) * ROW,
	);

	function place(s) {
		const byId = {};
		const put = (cells, col) =>
			(cells ?? []).map((c, k) => (byId[c.id] = { ...c, x: col.x, y: TOP + k * ROW, w: col.w, col }));
		const cells = [...put(s.stack, STACK), ...put(s.heap, HEAP)];
		for (const c of cells) {
			const t = c.pointsTo ? byId[c.pointsTo] : null;
			c.shown = t ? t.addr : (c.value ?? '');
			c.target = t;
		}
		return { cells, byId };
	}

	const now = $derived(place(step));
	const before = $derived(i > 0 ? place(data.steps[i - 1]).byId : {});

	const changed = (c) => {
		const b = before[c.id];
		return i > 0 && (!b || b.shown !== c.shown || !!b.freed !== !!c.freed);
	};

	const arrows = $derived(
		now.cells
			.filter((c) => c.target)
			.map((c) => {
				const t = c.target;
				const loop = t.col === c.col;
				return {
					id: c.id,
					loop,
					danger: !!t.freed,
					x1: c.x + c.w,
					y1: c.y + CELL_H / 2 - (loop ? 6 : 0),
					x2: loop ? t.x + t.w + 7 : t.x - 7,
					y2: t.y + CELL_H / 2 + (loop ? 6 : 0),
				};
			}),
	);
</script>

<figure class="viz not-content">
	<div class="panes">
		<pre class="code" aria-label="예제 코드">{#each lines as text, n}<span class="line" class:current={n + 1 === step.line}><span class="no">{n + 1}</span>{text || ' '}
</span>{/each}</pre>

		<svg viewBox="0 0 {width} {height}" role="img" aria-label="메모리 상태: {step.note}">
			<defs>
				{#each ['ok', 'danger'] as kind}
					<marker id="{uid}-{kind}" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="7" markerHeight="7" orient="auto">
						<path d="M 0 0 L 10 5 L 0 10 z" class="head {kind}" />
					</marker>
				{/each}
			</defs>

			<text class="region" x={STACK.x} y="18">스택</text>
			{#if hasHeap}<text class="region" x={HEAP.x} y="18">힙</text>{/if}

			{#each now.cells as c (c.id)}
				<g in:fly={{ y: -12, duration: 300 }} out:fade={{ duration: 150 }}>
					<rect class="cell" class:freed={c.freed} x={c.x} y={c.y} width={c.w} height={CELL_H} rx="6" />
					{#if changed(c)}
						{#key i}
							<rect class="flash" x={c.x} y={c.y} width={c.w} height={CELL_H} rx="6" />
						{/key}
					{/if}
					<text class="name" x={c.x + 12} y={c.y + 20}>{c.name ?? '(이름 없음)'}</text>
					<text class="type" x={c.x + 12} y={c.y + 37}>{c.type}</text>
					{#key c.shown + (c.freed ? '!' : '')}
						<text class="value" class:freed={c.freed} x={c.x + c.w - 12} y={c.y + 21} in:fade={{ duration: 350 }}>
							{c.freed ? '해제됨' : c.shown}
						</text>
					{/key}
					<text class="addr" x={c.x + c.w - 12} y={c.y + 38}>주소 {c.addr}</text>
					{#each c.aliases ?? [] as alias, k (alias)}
						<g in:fly={{ x: 16, duration: 350 }} out:fade={{ duration: 150 }}>
							<rect class="alias" x={c.x + 64 + k * 78} y={c.y - 10} width="70" height="20" rx="10" />
							<text class="alias" x={c.x + 99 + k * 78} y={c.y + 4}>별명 {alias}</text>
						</g>
					{/each}
				</g>
			{/each}

			{#each arrows as a (a.id)}
				<Arrow {...a} marker="{uid}-{a.danger ? 'danger' : 'ok'}" />
			{/each}
		</svg>
	</div>

	<figcaption>
		<p class="note" aria-live="polite">{step.note}</p>
		{#if step.output}
			<pre class="output"><span class="label">출력</span>{step.output}</pre>
		{/if}
		<div class="controls">
			<button onclick={() => (i = 0)} disabled={i === 0}>처음으로</button>
			<button onclick={() => i--} disabled={i === 0}>← 이전</button>
			<button class="primary" onclick={() => i++} disabled={i === last}>다음 →</button>
			<span class="count">{i + 1} / {data.steps.length}</span>
		</div>
	</figcaption>
</figure>

<style>
	.viz {
		--viz-danger: var(--palette-error);
		margin: 1.5rem 0;
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.5rem;
		overflow: hidden;
		background: var(--sl-color-bg-nav);
	}
	.panes {
		display: grid;
		grid-template-columns: fit-content(58%) minmax(0, 1fr);
		align-items: start;
	}
	@media (max-width: 60rem) {
		.panes {
			grid-template-columns: minmax(0, 1fr);
		}
	}
	.code {
		margin: 0;
		padding: 0.75rem 0;
		font-family: var(--__sl-font-mono);
		font-size: 0.875rem;
		letter-spacing: 0;
		line-height: 1.65;
		overflow-x: auto;
		background: transparent;
		border: 0;
	}
	.line {
		display: block;
		padding-right: 1rem;
		border-left: 3px solid transparent;
		transition: background-color 0.25s;
	}
	.line.current {
		background: var(--sl-color-accent-low);
		border-left-color: var(--sl-color-accent);
	}
	.no {
		display: inline-block;
		width: 2.4em;
		margin-right: 0.8em;
		text-align: right;
		color: var(--sl-color-gray-3);
		user-select: none;
	}
	svg {
		display: block;
		width: 100%;
		max-width: 34rem;
		margin: 0 auto;
		padding: 0.5rem;
		font-family: var(--__sl-font-mono);
	}
	.region {
		font-family: var(--__sl-font);
		font-size: 12px;
		font-weight: 600;
		fill: var(--sl-color-gray-3);
	}
	.cell {
		fill: var(--sl-color-bg);
		stroke: var(--sl-color-gray-4);
	}
	.cell.freed {
		stroke: var(--viz-danger);
		stroke-dasharray: 5 4;
	}
	.flash {
		fill: var(--sl-color-accent);
		opacity: 0;
		pointer-events: none;
		animation: flash 0.9s ease-out;
	}
	@keyframes flash {
		from {
			opacity: 0.45;
		}
		to {
			opacity: 0;
		}
	}
	.name {
		font-size: 15px;
		font-weight: 700;
		fill: var(--sl-color-white);
	}
	.type {
		font-size: 11px;
		fill: var(--sl-color-gray-3);
	}
	.value {
		font-size: 16px;
		font-weight: 700;
		text-anchor: end;
		fill: var(--sl-color-text-accent);
	}
	.value.freed {
		fill: var(--viz-danger);
		font-family: var(--__sl-font);
		font-size: 13px;
	}
	.addr {
		font-size: 10px;
		text-anchor: end;
		fill: var(--sl-color-gray-3);
	}
	rect.alias {
		fill: var(--sl-color-accent);
	}
	text.alias {
		font-family: var(--__sl-font);
		font-size: 11px;
		font-weight: 600;
		text-anchor: middle;
		fill: var(--sl-color-black);
	}
	.head.ok {
		fill: var(--sl-color-accent);
	}
	.head.danger {
		fill: var(--viz-danger);
	}
	figcaption {
		padding: 0.75rem 1rem 1rem;
		border-top: 1px solid var(--sl-color-gray-5);
		background: var(--sl-color-bg);
	}
	.note {
		min-height: 3.2em;
		margin: 0 0 0.5rem;
		font-size: 0.95rem;
	}
	.output {
		font-family: var(--__sl-font-mono);
		margin: 0 0 0.75rem;
		padding: 0.4rem 0.7rem;
		font-size: 0.82rem;
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.3rem;
		background: var(--sl-color-bg-nav);
	}
	.label {
		margin-right: 0.8em;
		font-family: var(--__sl-font);
		font-size: 0.75rem;
		color: var(--sl-color-gray-3);
	}
	.controls {
		display: flex;
		flex-wrap: wrap;
		align-items: center;
		gap: 0.5rem;
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
		opacity: 0.4;
		cursor: default;
	}
	.count {
		margin-left: auto;
		font-size: 0.8rem;
		color: var(--sl-color-gray-3);
	}
	@media (prefers-reduced-motion: reduce) {
		.flash {
			animation: none;
		}
	}
</style>
