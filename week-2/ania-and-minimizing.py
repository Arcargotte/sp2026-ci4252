# B. Ania and Minimizing

# Este fue el primer problema de la tarea que hice. Me pareció  muy sencillo al principio -y, afortunadamente, lo fue de principio a fin. Aquí aplicamos un criterio greedy
# que consiste en lo siguiente:

# 1. Si tenemos un N de más de un dígito, el número más pequeño que podemos conformar cambiando a lo sumo k caracteres sin "leading zeroes" es aquel que tiene un 1 en 
#    la posicion decimal mas significativa y k - 1 0s 
# 2. Si N tiene un digito, la respuesta inmediatamente es 0.

# Podemos garantizar matemáticamente que cualquier número N a la que se apliquen las k sustituciones siguiendo este patrón es el mínimo que se puede conseguir. 

import math

t = list(map(int, input().split()))
n = input()

digits = t[0]
k = t[1]

minimum = ""

if (digits == 1 and k == 1):
    minimum += "0"
elif (k < 1):
    minimum = n
else:    
    for i in range(0, digits):
        if (k != 0):
            digit = int(n[i]) 
            if (i == 0 and digit > 1):
                k -= 1
                minimum += "1"
            elif (i > 0 and digit > 0):
                k -= 1
                minimum += "0"
            else:
                minimum += n[i]
        else:
            minimum += n[i:]
            break

print(minimum)
