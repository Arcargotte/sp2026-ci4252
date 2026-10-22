# ANARC09A - Seinfield

# Con programación dinámica (DP) - Bottom-Up

# Aquí implementamos la misma lógica que en CPP, pero este código dio TLE en SPOJ.


cases = []

while True:
    case = "".join(input().split())
    if "-" in case:
        break
    else:
        cases.append(case)

for i, case in enumerate(cases):
    n = len(case)
    dp = [0] + [float('inf')] * n
    
    for char in case:
        next_dp = [float('inf')] * (n + 1)
        for bal in range(n):
            if dp[bal] == float('inf'):
                continue
                
            costo_open = 0 if char == '{' else 1
            next_dp[bal + 1] = min(next_dp[bal + 1], dp[bal] + costo_open)
            
            if bal > 0:
                costo_close = 0 if char == '}' else 1
                next_dp[bal - 1] = min(next_dp[bal - 1], dp[bal] + costo_close)
                
        dp = next_dp