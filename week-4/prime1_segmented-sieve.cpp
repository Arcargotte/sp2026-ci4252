/*
    PRIME1 - Prime Generator
    
    Gracias a la bibliografía del curso y lo visto en clase pudo implementarse este algoritmo

    Con la idea de la criba de Eratostenes fue implementada desde la versión inocente del programa que resolviera PRIME1 hasta la versión dela criba
    segmentada recomendada como optimización para la resolución de este problema.

    La idea general de la criba consiste en generar una lista de números desde 2 a una cota superior con el fin de ir marcando los números primos en dicho intervalo.
    Iterativamente comenzamos desde el cuadrado del primo más pequeño en nuestra lista y de aquí en adelante eliminamos de la criba todos sus múltiplos. Repetimos
    este proceso hasta que el cuadrado supere a la cota superior y así en la lista quedarán solo los números primos en el rango descrito.

    Dado los primos desde 2 a N, la primera optimización consiste en darse cuenta que todo número compuesto a partir de sqrt(N) es producto de los primos encontrados
    hasta sqrt(N), por lo que solo necesitamos generar estos primos y eliminar sus múltiplos del resto de la lista en vez de recorrerla de principio a fin como 
    en la versión anterior.

    La siguiente optimización del algoritmo corresponde a una mejoraría en el uso de la memoria y, a su vez, implementa la solución que buscamos para este problema
    en particular. Para ello, sea s una constante cualquiera,

    (i) s determina el tamaño de los floor(N / s) bloques de números que vamos a definir, y el k bloque con 0<=k<=floor(N / s) contiene los 
        enteros del segmento [k * s, k*s + s - 1]
    (ii) Generamos los primos hasta sqrt(N) e iteramos sobre ellos en el bloque k con el fin de eliminar sus múltiplos en este bloque
        Respecto a este último, nos damos cuenta de lo siguiente: estamos manejando una lista de 0 hasta N de donde debemos marcar qué enteros son primos
        y cuáles no. Para acceder a los enteros contenidos en los bloques y eliminarlos respectivamente de la lista, accedemos al primer elemento indexado del k bloque
        con k * S y buscamos el primer múltiplo de un primo contenido en el rango del bloque accediendo a él directamente con floor(k * S / p) para un primo p.
        Luego, accedemos a la lista de verificación de primos y accedemos al índice verdadero que le corresponde al entero del bloque en la lista completa y lo 
        marcamos como "no primo".
        
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<char> segmented_sieve(long long L, long long R) {
    // generate all primes up to sqrt(R)
    long long lim = sqrt(R);
    vector<char> mark(lim + 1, false);
    vector<long long> primes;
    for (long long i = 2; i <= lim; ++i) {
        if (!mark[i]) {
            primes.emplace_back(i);
            for (long long j = i * i; j <= lim; j += i)
                mark[j] = true;
        }
    }

    vector<char> isPrime(R - L + 1, true);
    for (long long i : primes)
        for (long long j = max(i, (L + i - 1) / i) * i; j <= R; j += i)
            isPrime[j - L] = false;
    for (long long x = L; x <= min(R, 1LL); x++)
        isPrime[x - L] = false;
        
    return isPrime;
}

int main(){
    
    int t;
    cin >> t;
    vector<vector<long long int>> cases;
    int i = 0;
    long long L;
    long long R;

    while (i < t){
        cin >> L >> R;
        cases.push_back({L, R});
        i++;
    }
    i = 0;
    while (i  < t) {
        vector<char> primes = segmented_sieve(cases[i][0], cases[i][1]);
        
        long long index = 0;
        L = cases[i][0];

        for (long long j : primes){
            if (j) {
                cout << index + L << endl;
            }
            index++;
        }
        cout << endl;
        i++;
    }

    return 0;
}