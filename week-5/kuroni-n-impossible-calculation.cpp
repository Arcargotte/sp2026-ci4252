/* Kuroni and Impossible Calculation

    Me gustó mucho este problema porque fue sencillo. Aunque no me parecía trivial la aplicación del principio del palomar.

    La lógica es sencilla: solamente debemos multiplicar el valor absoluto de la diferencia entre todos los pares posibles del arreglo de enteros que se nos entrega.
    Pero podemos optimizar este problema determinando cuando una de estas diferencias es 0, tal que ese sea el resultado a retornar sin tener que recorrer todos
    los pares posibles. Aquí "aplicamos" el principio del palomar, pues notamos que es equivalente calcular el módulo m de una diferencia a calcular el módulo m
    del sustraendo y el minuendo. Del arreglo de enteros, queremos determinar si hay una repetición de uno de ellos módulo m (que en la caja correspondiente al valor
    del módulo m, haya al menos más de 1 número), pues de ser ese el caso entonces cuando calculemos la diferencia entre ellos nos va a dar 0 y toda la productoria
    retornará 0.
*/

#include <iostream>

using namespace std;

int main(){

    long long int m, n;
    cin >> n >> m;

    long long int arr[n];
    bool modulo_m [m] = {false};
    bool repeated = false;

    for(int i = 0; i < n; i++){

        cin >> arr[i];

        if(modulo_m[arr[i] % m]){
            repeated = true;
        }

        modulo_m[arr[i] % m] = true;
    }

    if (repeated) {
        cout << 0 << endl;
    } else {
        long long int ans = 1;
        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                ans = (ans * ((abs(arr[i] - arr[j]) % m))) % m;
            }
        }
        cout << ans << endl;
    }

    return 0;
}