# ANARC09A - Seinfield

# Estrategia Greedy:

# Haciéndole caso a los comentarios del problema y en virtud de lo solicitado en la tarea, implementamos una estrategia Greedy
# que consiste en los siguientes pasos:

# 1. Leer de izquierda a derecha el string s

# 2. Incluir en una pila el caracter leído.
#    Tenemos la intención de eliminar de s aquellos pares de llaves de apertura y cierre que ya sean balanceados. Es decir
#    cada vez que en el tope de la pila nos encontremos con { y el siguiente elemento leido sea } eliminamos el par {} 

# 3. Mientras que la pila no esté vacía, hacemos pop() a la pila dos veces para tomar un par de llaves, de manera que caemos en
#    en los siguientes casos:
#    '}' y '}':
#     Sumamos +1 a las operaciones necesarias para balancear s.
#    '{' y '{'
#     Sumamos +1 a las operaciones para balancear s.
#    '}' y '{'
#     Summamos +2 a las operaciones para balancear s.

# Como la longitud de s es par y eliminar un substring t ya balanceado mantiene la paridad de s, podemos asegurarnos de que la pila
# siempre tiene una cantidad par de elementos. 
# Asimismo, podemos garantizar que la estrategia Greedy retorna un resultado óptimo porque notamos que no eliminar ts que ya están balanceados
# suma +1 innecesariamente a la cantidad de operaciones total para balancear s, por lo que resulta mayor al mínimo anteriormente conseguido

cases = []

while True:
    case = "".join(input().split())
    if "-" in case:
        break
    else:
        cases.append(case)

for i, case in enumerate(cases):
    
    case_stack = []
    
    for c in case:
        if(len(case_stack) == 0):
            case_stack.append(c)
        else:
            if(c == '}' and case_stack[-1] == '{'):
                case_stack.pop()
            else:
                case_stack.append(c)
                
    ops = 0
    if(len(case_stack) == 0):
        print(f"{i + 1}. {ops}")
    else:
        while(len(case_stack) != 0):
            r = case_stack.pop()
            l = case_stack.pop()
            
            if(l == '{' and r == '{'):
                ops += 1
            elif(l == '}' and r == '}'):
                ops += 1
            else:
                ops += 2
                
        print(f"{i + 1}. {ops}")