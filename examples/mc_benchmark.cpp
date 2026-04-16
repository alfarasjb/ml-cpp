//
// Created by Jay on 4/17/2026.
//

// Benchmark harness — dumps timing CSV for speedup curve plots
//
// Sweep: N in {1M, 10M, 100M} x threads in {1, 2, 4, 8, max} x backend in {serial, async, pool}
// Warm-up runs + median of 5 trials per configuration
// Output: bench_results.csv with columns [backend, N, threads, median_ms, price, SE]
//
// Same test params as mc_demo: S0=100, K=100, r=0.05, sigma=0.20, T=1.0
