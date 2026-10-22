# A. Homework

# Aquí aplicamos una estrategia Greedy que podemos generalizar en los siguientes pasos:

# 1. Identificamos las letras diferentes que hay en la tarea y la proporción que tienen con respecto a la cantidad total de letras a estudiar

# 2. Ordenamos de forma ascendente el diccionario que almacenan los pares (letra, proporción)

# 3. Eliminamos de la tarea aquellas letras con menor proporción solo si eliminándolas no nos deja por debajo del límite de letras k

# Identificar la estrategia para hacer este ejercicio fue relativamente sencillo. Aunque interpretar la semántica de las salidas según el primer caso de prueba
# me costó. ¿Qué quiere decir que del string ´aaaaa´ no pueda eliminar no más de k caracteres? Como el string se compone de una solo caracter (le letra a), entonces
# realmente solo podemos quedarnos con 1 diferentes caracteres y que el string resultante son strings tales que no han perdido más de k caracteres. E imprimimos en 
# la salida un string representativo de esta clase que elimina la i-ésima clase de caracter tal que podemos al final garantizar obtener la cantidad mínima posible 
# de diferentes caracteres a mantener en el string.

import math

s = input()
k = int(input())
size = len(s)
boxes = 0

letters = {}
for i in range(0, size):
    if s[i] not in letters:
        letters[s[i]] = 1 / size
        boxes = boxes + 1
    else:
        letters[s[i]] += 1 / size
letters = dict(sorted(letters.items(), key=lambda item: item[1]))

acc = 0
minus_boxes = 0
for letter in letters:
    occurs = s.count(letter)
    if acc + (occurs) > k:
        break
    else:
        acc += occurs
        minus_boxes = minus_boxes + 1
        s = s.replace(letter,"")

print(int(boxes - minus_boxes))
print(s)
