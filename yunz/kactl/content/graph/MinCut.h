/**
 * Author: Simon Lindholm
 * Date: 2015-05-13
 * Source: Wikipedia
 * Description: 跑完最大流后, $s$-$t$ 最小割的 $s$ 侧就是从 $s$ 出发,
 * 只走剩余容量为正的边所能到达的所有点.
 * Usage: d.calc(s, t); // 先用 Dinic 等跑最大流
 * d.leftOfMinCut(v) // 为真则 v 在 s 侧
 * 割边 = 所有从 s 侧指向 t 侧的原边 (u, v)
 * Status: works
 */
