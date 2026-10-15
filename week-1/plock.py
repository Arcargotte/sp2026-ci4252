import math
import bisect

"""
PLONK - Where to Drink the Plonk?

:param friends: lista de 2-lista que contienen las coordenadas del i-ésimo amigo dado como entrada al problema
:param t: longitud de la lista friends
:return: Suma de las distancias con respecto a la coordenada del amigo tal que es mínima

A nota personal, este problema fue frustrante hacerlo. Erróneamente asumí que una heurística sería lo suficientemente buena para aprobar todos los casos de prueba
de Spoj haciéndome recordar mi experiencia con usted en Lab. de Algos II. ¡Qué difícil me fue llegar a la solución! Y estuve trabajando de más en esta heurística. Lo
bueno fue que aprendí que la mediana minimiza la suma de las distancias y que existe una manera de optimizar esta suma mediante un arreglo de sufijos (aunque creo que
un árbol de segmentos es conveniente considerando el problema en un contexto dinámico). Como el camino entre cualquier par de amigos se calcula con la 
distancia Manhattan, la cual es independiente del camino, reducimos el problema a encontrar un valor xi y un valor yi perteneciente al par (x,y) del i-esimo amigo en friends
que minimiza la suma de las distancias de los amigos respecto a su coordenada x y respecto a su coordenada y. Para calcular el mínimo, debemos calcular eficientemente
la suma de las distancias con respecto a cada amigo y tomar el menor de todos, así que ordenamos ambas listas de coordenadas x y coordenadas con mergeSort y con un arreglo
de sufijos calculamos las distancias en orden constante
"""

def merge_sort(arr):
    if len(arr) <= 1:
        return arr

    mid = len(arr) // 2
    left_half = arr[:mid]
    right_half = arr[mid:]

    left_sorted = merge_sort(left_half)
    right_sorted = merge_sort(right_half)

    return merge(left_sorted, right_sorted)


def merge(left, right):
    sorted_arr = []
    i = j = 0

    while (i < len(left) and j < len(right)):
        if (left[i] <= right[j]):
            sorted_arr.append(left[i])
            i += 1
        else:
            sorted_arr.append(right[j])
            j += 1

    sorted_arr.extend(left[i:])
    sorted_arr.extend(right[j:])

    return sorted_arr

def get_sum_dist(val, sorted_arr, pref_sums, t):

    idx = bisect.bisect_left(sorted_arr, val)

    # Puntos a la izquierda (menores a val)
    left_sum = idx * val - pref_sums[idx]
    # Puntos a la derecha (mayores o iguales a val)
    right_sum = (pref_sums[t] - pref_sums[idx]) - (t - idx) * val

    return left_sum + right_sum

def plock(friends, t):
    x_coords = []
    y_coords = []
    for friend in friends:
        x_coords.append(friend[0])
        y_coords.append(friend[1])
    x_coords = merge_sort(x_coords)
    y_coords = merge_sort(y_coords)

    pref_x = [0] * (t + 1)
    pref_y = [0] * (t + 1)
    for i in range(0, t):
        pref_x[i + 1] = pref_x[i] + x_coords[i]
        pref_y[i + 1] = pref_y[i] + y_coords[i]

    min_total_dist = math.inf

    for fx, fy in friends:
        dist_x = get_sum_dist(fx, x_coords, pref_x, t)
        dist_y = get_sum_dist(fy, y_coords, pref_y, t)
        total_dist = dist_x + dist_y

        if total_dist < min_total_dist:
            min_total_dist = total_dist

    return min_total_dist

n = int(input())
for i in range(0, n):
    t = int(input())
    friends = []
    for j in range(0, t):
        friends.append(list(map(int, input().split())))
    print(plock(friends, t))