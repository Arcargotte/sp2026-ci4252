# C. Vanya and Exams

# Este problema me presentó un desafío a lo que respecta en el aspecto de optimización. La estrategia greedy a aplicar es clara:

# 1.    Ordena de menor a mayor los pares (calificación_i, ensayos_i) según ensayos, donde calificación_i es la nota recibida en el i-ésimo examen y ensayos_i es la cantidad
#       de ensayos a hacer para aumentar calificación_i en una unidad
# 2.    Hasta que logremos conseguir el promedio requerido para la beca, haremos tantos ensayos posibles para llegar a la nota final en el i-ésimo examen.

# Como la lista está ordenada de forma ascendente, garantizamos hacer el mínimo de ensayos posibles. Sin embargo, en mi caso el reto consistía en hallar una manera de optimizar
# las operaciones a realizar para que CodeForces aceptara mi solución. Esta optimización consistió en lo siguiente:

# - Sea req_grade_avg * num_exams la suma total de las notas a conseguir en los exámenes. Usar esta condición como función de cota es óptima, pues es un cálculo que realizamos
#   solo una vez comparado a calcular por cada iteración el nuevo promedio que obtendríamos de haber aumentado nuestra calificación a la máxima ponderada haciendo 
#   (max_grade - calificación_i) * ensayos_i ensayos.

# - Por cada iteración determinamos los puntos que nos faltan para alcanzar la suma mínima requerida de calificaciones para tener el promedio requerido y los puntos que
#   podríamos conseguir haciendo una cantidad de ensayos_i. De aquí buscamos el mínimo de ellos que nos garantiza hacer la cantidad minima de ensayos para o conseguir la suma
#   que necesitamos para tener el promedio requerido o la cantidad de ensayos que podemos hacer limitada por la calificación que tenemos y a la que podríamos alcanzar su máximo.
#   Luego, sumamos de golpe los ensayos que nos faltan por hacer y actualizamos nuestra suma de puntos.

n = list(map(int, input().split()))
grade_req = []

num_exams = n[0]
max_grade = n[1]
req_grade_avg = n[2]

for i in range(0, num_exams):
    grade_req.append(list(map(int, input().split())))

curr_avg_sum = sum(pair[0] for pair in grade_req)
avg = curr_avg_sum / num_exams
grade_req = sorted(grade_req, key=lambda pair: pair[1])

num_essays = 0
i = 0

curr_sum = curr_avg_sum
target_sum = req_grade_avg * num_exams
while (curr_sum < target_sum and i < num_exams):
    points_needed = target_sum - curr_sum
    points_obtainable = max_grade - grade_req[i][0]
    points_to_add = min(points_needed, points_obtainable)

    if points_to_add > 0:
        num_essays += points_to_add * grade_req[i][1]
        curr_sum += points_to_add
        grade_req[i][0] += points_to_add
    
    i = i + 1

print(num_essays)