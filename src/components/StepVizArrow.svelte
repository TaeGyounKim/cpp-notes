<script>
	import { Tween } from 'svelte/motion';
	import { cubicOut } from 'svelte/easing';
	import { fade } from 'svelte/transition';

	let { x1, y1, x2, y2, loop = false, danger = false, marker } = $props();

	// 화살표 끝점이 바뀌면 부드럽게 따라간다.
	const pos = Tween.of(() => ({ x1, y1, x2, y2 }), { duration: 450, easing: cubicOut });

	const d = $derived.by(() => {
		const p = pos.current;
		if (loop) {
			const k = 34 + Math.abs(p.y2 - p.y1) * 0.22;
			return `M ${p.x1} ${p.y1} C ${p.x1 + k} ${p.y1}, ${p.x2 + k} ${p.y2}, ${p.x2} ${p.y2}`;
		}
		const mx = (p.x1 + p.x2) / 2;
		return `M ${p.x1} ${p.y1} C ${mx} ${p.y1}, ${mx} ${p.y2}, ${p.x2} ${p.y2}`;
	});
</script>

<path {d} class:danger marker-end="url(#{marker})" in:fade={{ duration: 300 }} out:fade={{ duration: 150 }} />
<circle cx={pos.current.x1} cy={pos.current.y1} r="3.5" class:danger in:fade={{ duration: 300 }} out:fade={{ duration: 150 }} />

<style>
	path {
		fill: none;
		stroke: var(--sl-color-accent);
		stroke-width: 2;
	}
	circle {
		fill: var(--sl-color-accent);
	}
	path.danger {
		stroke: var(--viz-danger);
		stroke-dasharray: 5 4;
	}
	circle.danger {
		fill: var(--viz-danger);
	}
</style>
