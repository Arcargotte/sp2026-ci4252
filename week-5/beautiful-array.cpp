/* Beautiful Array

    Ideando la solución de este problema me di cuenta que accidentalmente deduje algo llamado "Algoritmo de Kadane" para determinar la belleza de un arreglo. Lo 
    descarté inmediatamente como algo "inútil" porque simplemente no se me ocurría una manera de adaptarlo a este problema, aun si no tuviese justificación
    alguna. Que esta experiencia refleje la importancia de confiar en uno mismo y de insistir hasta que no queden alternativas para una candidata a resolución de un
    problema.

    En la medida que recorramos el arreglo a nos enfrentamos a estas decisiones:
    - ¿Vale la pena seguir la racha sumando este elemento sin escalarlo por x o comenzar de nuevo desde aquí?
        Esta información la guarda la variable s1, que nos va a indicar si vale la pena siquiera escalar por x o no
    - ¿Vale la pena iniciar la multiplicación por el escalar x en el i-ésimo elemento o seguir la racha que llevamos desde el anterior?
        La información la dice s2, que nos indica si deberíamos seguir en el sub-arreglo escalado por x o si deberíamos a escalar en el elemento
        siguiente a la sumatoria indicada por s1 
    - ¿Vale la pena terminar la multiplicación por el escalar x en el i-ésimo elemento, o seguir sumando los elementos sin escalarlos por x?
        s3 guarda esta información y nos indica si es mejor continuar con la sumatoria tomando en cuenta que el útimo elemento considerado es el último
        elemento del subarreglo escalado o si deberíamos seguir sumando los elementos del arreglo considerando que el último del subarreglo lo dejamos atrás
    
    Retornamos al final el máximo entre s1, s2 y s3.


*/

#include <iostream>
#include <algorithm>

using namespace std;

int main() {

    int n;
    long long x;
    
    cin >> n >> x;

    long long s1 = 0; // Estado anterior a iniciar la multiplicación por x
    long long s2 = 0; // Estado durante  la multiplicación por x
    long long s3 = 0; // Estado después de haber multiplicado
    long long max_beauty = 0;

    for (int i = 0; i < n; i++) {
        long long v;
        cin >> v;

        // Siempre comparamos con 0, porque el subarreglo vacío tiene sumatoria 0 y es máximo cuando todas las sumatorias posibles en el arreglo son negativas.
        s3 = max(0LL, max(s2, s3) + v);
        s2 = max(0LL, max(s1, s2) + v * x);
        s1 = max(0LL, s1 + v);

        // Actualizamos la respuesta global con el mejor escenario hasta ahora
        max_beauty = max({max_beauty, s1, s2, s3});
    }

    cout << max_beauty << endl;

    return 0;
}