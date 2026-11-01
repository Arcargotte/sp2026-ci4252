/*  Interval Mod

    Estudiando el problema sin la restriccion de la ventana, notamos que calcular el mínimo de la sumatoria de los valores del arreglo
    equivale a calcular el mínimo entre (módulo p) y (módulo q módulo p) de cada elemento y aplicar la sumatoria.

    Consideremos ahora una ventana de tamaño k sobre la que hacemos o la operación (módulo p) o (módulo q módulo p). Para minimizar
    los valores fuera de la ventana, la desplazamos hacia un valor fuera de ella y determinamos cuál del par de las operaciones la minimiza mejor, y
    como tenemos que aplicar esta operación sobre los elementos que estaban en la ventana anteriormente no las afecta, la sumatoria se mantiene y el proceso
    se minimización consiste en calcular todas las ventanas posibles y determinar cuál es su mejor operador para sumarle los mínimos de todos los valores
    fuera de ella. 

    Como este proceso es tardado, se usa una suma de prefijos para calcular inmediatamente las sumatorias de los elementos en la ventana y fuera de ella.
    De cada ventana que calculemos, nos quedamos con aquella que nos retorne el mínimo.
*/

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

int main() {

    int t;
    cin >> t;

    while(t--){
        
        int n, k;
        long long p, q;
        cin >> n >> k >> p >> q;

        vector<long long> a;

        for(int i = 0; i < n; i++){
            long long val;
            cin >> val;
            a.push_back(val);
        }

        vector<vector<long long>> strategy_mod(2, vector<long long>(n, 0));

        vector<long long> each_min(n);

        int index = 0;
        for(long long x : a){
            
            // Guardo ambos posibles módulos para cada valor
            strategy_mod[0][index] = x % p;
            strategy_mod[1][index] = (x % q) % p;

            // Guardo el mínimo de cada valor
            each_min[index] = min(strategy_mod[0][index], strategy_mod[1][index]);

            index++;
        }

        // Hacemos que strategy_mod y each_min sean arreglos de prefijos
        for(int i = 1; i < n; i++){
            strategy_mod[0][i] += strategy_mod[0][i-1];
            strategy_mod[1][i] += strategy_mod[1][i-1];
            each_min[i] += each_min[i-1];
        }


        long long optimal_result = numeric_limits<long long>::max(); //Centinela

        // Por último, recorro cada una de las ventanas y me quedo con la mejor
        for(int i = k - 1; i < n; i++){
            long long left  = (i - k >= 0) ? each_min[i - k] : 0;
            long long window_val_strategy_0 = strategy_mod[0][i] - (i - k >= 0 ? strategy_mod[0][i - k] : 0);
            long long window_val_strategy_1 = strategy_mod[1][i] - (i - k >= 0 ? strategy_mod[1][i - k] : 0);
            long long right = each_min[n - 1] - each_min[i];

            // Determinamos con min cuál fue la mejor estrategia para minimizar el valor de la ventana
            long long possible_optimal = left + min(window_val_strategy_0, window_val_strategy_1) + right;
            
            if(possible_optimal < optimal_result){
                optimal_result = possible_optimal;
            }
            
        }

        cout << optimal_result << endl;
    }

}
