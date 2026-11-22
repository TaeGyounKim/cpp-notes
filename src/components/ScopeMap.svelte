<script>
	/*
	 * 이름이 어느 범위(네임스페이스 등)에 들어 있는지와, 어떤 코드가 그중 무엇을 찾아가는지 보여 준다.
	 * data = {
	 *   root: Scope,
	 *   queries: [{ code, hits: string[], ok: boolean, note }]
	 * }
	 * Scope = { label, items?: [{ id, text }], children?: Scope[] }
	 */
	let { data } = $props();
	let selected = $state(0);
	const query = $derived(data.queries[selected]);
</script>

{#snippet scope(s)}
	<div class="scope">
		<span class="label">{s.label}</span>
		<div class="body">
			{#each s.items ?? [] as item (item.id)}
				<code class="item" class:hit={query.hits.includes(item.id)} class:bad={!query.ok}>{item.text}</code>
			{/each}
			{#each s.children ?? [] as child}
				{@render scope(child)}
			{/each}
		</div>
	</div>
{/snippet}

<figure class="map not-content">
	<div class="panes">
		<div class="queries" role="tablist" aria-label="코드 고르기">
			{#each data.queries as q, n}
				<button role="tab" aria-selected={n === selected} class:on={n === selected} onclick={() => (selected = n)}>
					<pre>{q.code}</pre>
				</button>
			{/each}
		</div>
		<div class="scopes">
			{@render scope(data.root)}
		</div>
	</div>
	<figcaption aria-live="polite">
		<span class="status" class:bad={!query.ok}>{query.ok ? '찾음' : '컴파일 오류'}</span>
		{query.note}
	</figcaption>
</figure>

<style>
	.map {
		margin: 1.5rem 0;
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.5rem;
		overflow: hidden;
		background: var(--sl-color-bg-nav);
	}
	.panes {
		display: grid;
		grid-template-columns: minmax(0, 5fr) minmax(0, 6fr);
		gap: 1rem;
		padding: 1rem;
	}
	@media (max-width: 60rem) {
		.panes {
			grid-template-columns: minmax(0, 1fr);
		}
	}
	.queries {
		display: flex;
		flex-direction: column;
		gap: 0.4rem;
	}
	button {
		padding: 0.45rem 0.7rem;
		text-align: left;
		color: var(--sl-color-white);
		background: var(--sl-color-bg);
		border: 1px solid var(--sl-color-gray-5);
		border-left: 3px solid transparent;
		border-radius: 0.3rem;
		cursor: pointer;
	}
	button.on {
		border-left-color: var(--sl-color-accent);
		background: var(--sl-color-accent-low);
	}
	pre {
		margin: 0;
		padding: 0;
		font-family: var(--__sl-font-mono);
		font-size: 0.875rem;
		line-height: 1.5;
		letter-spacing: 0;
		white-space: pre-wrap;
		border: 0;
		background: transparent;
	}
	.scope {
		padding: 0.5rem 0.6rem 0.6rem;
		border: 1px dashed var(--sl-color-gray-4);
		border-radius: 0.4rem;
		background: var(--sl-color-bg);
	}
	.scope .scope {
		background: var(--sl-color-bg-nav);
	}
	.label {
		display: block;
		margin-bottom: 0.4rem;
		font-size: 0.75rem;
		font-weight: 700;
		color: var(--sl-color-gray-3);
	}
	.body {
		display: flex;
		flex-direction: column;
		gap: 0.4rem;
	}
	.item {
		align-self: flex-start;
		padding: 0.15rem 0.55rem;
		font-family: var(--__sl-font-mono);
		font-size: 0.875rem;
		letter-spacing: 0;
		color: var(--sl-color-white);
		border: 1px solid var(--sl-color-gray-5);
		border-radius: 0.3rem;
		background: var(--sl-color-bg);
		transition:
			background-color 0.25s,
			border-color 0.25s,
			color 0.25s,
			transform 0.25s;
	}
	.item.hit {
		color: var(--sl-color-black);
		border-color: var(--sl-color-text-accent);
		background: var(--sl-color-text-accent);
		transform: translateX(0.4rem);
	}
	.item.hit.bad {
		border-color: var(--palette-error);
		background: var(--palette-error);
	}
	figcaption {
		min-height: 4.2em;
		padding: 0.75rem 1rem;
		font-size: 0.95rem;
		border-top: 1px solid var(--sl-color-gray-5);
		background: var(--sl-color-bg);
	}
	.status {
		display: inline-block;
		margin-right: 0.5rem;
		padding: 0.05rem 0.5rem;
		font-size: 0.75rem;
		font-weight: 700;
		color: var(--sl-color-black);
		border-radius: 999px;
		background: var(--sl-color-text-accent);
	}
	.status.bad {
		background: var(--palette-error);
	}
	@media (prefers-reduced-motion: reduce) {
		.item {
			transition: none;
		}
	}
</style>
