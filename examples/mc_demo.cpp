//
// Created by Jay on 4/17/2026.
//

// Smoke test / usage example
//
// Test params: S0=100, K=100, r=0.05, sigma=0.20, T=1.0
// Expected BS call price: ~10.4506
//
// 1. Compute BS closed-form price
// 2. Run serial MC at N=10M, print price + SE, compare to BS
// 3. Run async MC, verify matches serial
// 4. Run pool MC, verify matches serial
// 5. Print all three results side-by-side
