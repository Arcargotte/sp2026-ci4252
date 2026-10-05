import math
import sys

"""
(AI Solution) RMQSQ - Range Minimum Query

La siguiente solución fue escrita con inteligencia artificial.

Creo que podemos aprender de la IA tanto como ella puede aprender de nosotros (claro, si asumimos que realmente "aprende"). Comparado a los otros dos problemas, de los cuales
la IA solo sugirió cambios la azúcar sintáctica de Python para simplificar instrucciones o usar unas librerías que simplifican el trabajo de unos
cálculos, para RNQSQ sugirió algo completamente distinto a mi solución original. En vez de usar otra vez un árbol de segmentos, comenzó a usar una "sparse table" que, según su
comparación (aprovechando que el arreglo es estático), supera en tiempo de consulta al árbol de segmentos por hacerlo en tiempo constante a diferencia del árbol de segmentos
que lo hace en O(logN). El árbol de segmentos solo necesita O(N) para construirlo, comparado a la construcción de la tabla que es O(N Log N). Al final, se trata del caso de uso
que se le de a la estructura que convenga usarla o no (esto, aludiendo el hecho que soilo podemos usar la tabla esparsa cuando los datos son estáticos). Por el contexto del problema,
me parece una buena solución y sinceramente no se me ocurre dónde aplicar una mejora personal que haría la solución más eficiente.

Referencia de mi lectura sobre la tabla esparsa: https://cp-algorithms.com/data_structures/sparse-table.html
"""

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return

    N = int(input_data[0])
    ptr = 1

    A = [int(x) for x in input_data[ptr : ptr + N]]
    ptr += N

    # Precalcular log2
    lg = [0] * (N + 1)
    for i in range(2, N + 1):
        lg[i] = lg[i // 2] + 1

    LOGN = lg[N] + 1
    st = [[0] * N for _ in range(LOGN)]

    for i in range(N):
        st[0][i] = A[i]

    for k in range(1, LOGN):
        length = 1 << k
        half = 1 << (k - 1)
        for i in range(N - length + 1):
            st[k][i] = min(st[k - 1][i], st[k - 1][i + half])

    Q = int(input_data[ptr])
    ptr += 1

    out = []
    for _ in range(Q):
        L = int(input_data[ptr])
        R = int(input_data[ptr + 1])
        ptr += 2

        length = R - L + 1
        k = lg[length]
        res = min(st[k][L], st[k][R - (1 << k) + 1])
        out.append(str(res))

    print("\n".join(out))


if __name__ == "__main__":
    solve()