import math

"""
RMQSQ - Range Minimum Query

:param root: copia del nodo raíz del árbol de segmentos construido a partir de la entrada de n números
:param q: consulta del mínimo entre el par de índices i,j 
:return: mínimo del sub-arreglo T[i..j]

Este problema va como anillo al dedo al uso de un árbol de segmentos: la asociatividad del operador min asegura que el minimo en cualquier sub-arreglo T[i..j] no lo perdamos
en la k-ésima sub-consulta por compararlo con el mínimo obtenido de un par de sub-consultas a los sub-árboles izquierdos y derechos. Así, aplicando la plantilla existente 
para implementar un árbol de segmentos, creamos una clase nodo que contiene la información del sub-arreglo al que hace referencia, su mínimo y sus hijos izquierdo y derecho;
construimos una función auxiliar que crea el árbol de segmentos y rmqsq hace la consulta q.
"""

class Node:
    def __init__(self, i, j):
        self.lower_index = i
        self.upper_index = j
        self.min_value = math.inf

        self.left = None
        self.right = None

def build_tree(curr_arr, i, j):
    root = Node(i, j)

    if (i == j):
        root.min_value = curr_arr[i]
        return root

    mid = (i + j) // 2
    root.left = build_tree(curr_arr, i, mid)
    root.right = build_tree(curr_arr, mid + 1, j)

    root.min_value = min(root.left.min_value, root.right.min_value)

    return root

def rmqsq (root, q):

    if ((q[0] == root.lower_index and q[1] == root.upper_index)):
        return root.min_value
    if (q[0] == q[1]):
        if root.lower_index == root.upper_index:
            return root.min_value
    mid = (root.lower_index + root.upper_index) // 2
    if (q[1] <= mid):
        return rmqsq(root.left, q)
    elif (q[0] >= mid + 1):
        return rmqsq(root.right, q)
    else:
        return min(rmqsq(root.left, [q[0], mid]), rmqsq(root.right, [mid + 1, q[1]]))

n = int(input())
t = list(map(int, input().split()))
q = int(input())
qi = []

for i in range(0, q):
    qi.append(list(map(int, input().split())))

root = build_tree(t, 0, n - 1)

for i in range(0, q):
    print(rmqsq(root, qi[i]))
