# C. Liebig's Barrels

# Este problema fue implacable.

# Creo que la justificación está que venía de hacer los otros problemas con una estrategia Greedy en la que me fijaba rápidamente. Pero la que era aquí requerida era
# más sútil de lo que en un principio me imaginé. Ésto lo acredito a que cuando leí este problema pensé que me pedían el volumen máximo que podríamos obtener y determinar
# si cumplía o no con la propiedad de que los barriles eran "lo más parecidos posibles" (que llamaremos propiedad l). Realmente nos pedían un volumen máximal bajo l. Gracias
# a que hablé con un gran amigo mío fue que pude terminar de entender cómo resolver este problema. Así que aquí describo la estrategia Greedy que resuelve este problema:

# 1. Ordenar las "duelas" de los barriles de menor a mayor
#    Podemos derivar las siguientes propiedades en este problema: siempre existirá un barril cuyo volumen será la duela de tamaño mínimo en el problema y que deben existir
#    al menos n de entre las n * k duelas que cumplan la propiedad l. De no existir las n duelas, entonces el problema es irresoluable bajo la propiedad l. Como la lista
#    está ordenada, podemos determinar inmediatamente si existen las n duelas recorriendo el arreglo y contando si existen de entre las duelas las n que cumplen l

# 2. Si el problema es resoluble bajo l, entonces nos toca ahora optimizar nuestra selección de duelas tales que podamos maximizar la sumatoria del volumen de los barriles.
#    Nos fijamos que estamos maximizando cuando construimos un barril tomando k duelas adyacentes entre sí. Sin embargo, esto es un problema: del conjunto de duelas que son válidas
#    bajo l, si tomamos de k en k corremos el riesgo de quedarnos sin duelas válidas para poder formar los n barriles. Para solucionar esto, nos preguntamos si podemos
#    tomar k duelas adyacentes para el i-ésimo barril y si, tomándolas, todavía nos quedan n - i duelas con las que formar los barriles restantes.
#    Si es posible, tomamos las k duelas adyacentes. Si no, solo tomamos una sola duela y tomamos las demás que están afuera de nuestro conjunto de duelas
#    que cumplen l (de las que podemos garantizar su existencia porque hay n * k duelas).

# El problema se presta para una excelente optimización que mi amigo compartió conmigo y que estudiamos con la IA. Calculando el mínimo de unos "punteros" que apuntan
# a una posición del conjunto de duelas válidas dando un k-salto y a la posición que me asegura tener n - i duelas para poder construir los barriles restantes. 
# Si podemos dar k saltos y aun tener las n-i duelas para garantizar construir los barriles, damos el k-salto aumentando la posición señalada por el primer puntero y 
# reduciendo el otro en consecuencia; cuando el segundo resulta menor, entonces solo queda tomar las duelas restantes de 1 en 1.



params = list(map(int, input().split()))
n = params[0]
k = params[1]
l = params[2]

staves = list(map(int, input().split()))

staves.sort()

limit = staves[0] + l
total_volume = 0
valid_count = 0
i = 0

for stave in staves:
    if stave <= limit:
        valid_count += 1
    else:
        break

if (valid_count < n):
    print(0)
else:
    for b in range(n):
        total_volume += staves[i]
        i = min(i + k, valid_count - n + (b + 1))
    print(total_volume)
