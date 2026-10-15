"""
C - Modulo Summation

:param n: n valores enteros, con n mayor o igual que 2 y menor o igual a 3000
:param m: m enteros entre 2 y 10e5
:return: retorna el valor máximo alcanzable por f(l) = l mod a1 + l mod a2 + ... + m mod an

El valor máximo alcanzado por f viene dado por (a1 - 1) + (a2 - 1) + ... + (an - 1) por def. de las congruencias módulo ai. Conviene preguntarse
si existe algún entero que alcance tal valor y, efectivamente, es así: el mcm(a1, a2, ..., an). Esto se debe a que el mcm es el unico valor que "contiene"
a ai repetido a1a2...ai-1ai+1...an veces, de manera tal que si restamos 1 al mcm, obtenemos al máximo en todas las congruencias modulo ai. 
"""

n = int(input())
m = list(map(int, input().split()))
max_val = 0
for i in range(n):
    max_val += m[i]
print(max_val - n)