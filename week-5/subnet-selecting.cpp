/* Subnet Selecting

    Me parece que este problema está mal redactado o es que la notación no colabora a la idea tan sencilla que refleja MEX. 

    Básicamente, MEX es el entero no negativo más pequeño que no aparece en una colección de enteros. Decimos que "maximizamos MEX" porque avanzamos a partir
    del 0 y "aumentamos" la propuesta del MEX según podamos determinar qué grupos podemos formar para nuestra colección.

    Notamos lo siguiente: por definiciónd el MEX, necesitamos formar un grupo cuyo máximo sea el más pequeño de la colección. Esta es una idea que se rompe
    fácilmente en un arreglo de enteros, pues están ordenados y siempre existe un subconjunto de maximales que "desplazan" al MEX. Por lo tanto, debemos
    estudiar los elementos que forman parte de la colección sin formar los grupos y determinar la frecuencia absoluta con la que ocurren. Del candidato mex hasta n 
    (siendo n el máximo valor del arreglo de enteros), nos preguntamos si tenemos suficientes elementos en el arreglo tal que podamos formar al menos un grupo tal que
    mex pueda formar ser el máximo o no. Si no hay suficientes elementos en la colección, entonces el mex propuesto es el MEX verdadero; en caso contrario,
    seguimos iterando formando más grupos hasta que podamos concluir que no existen suficientes elementos para que el mex aparezca en la colección y sea el MEX verdadero,
    o hasta que nos encontremos con un mex que no aparezca en la colección original y podamos concluir que ese es el MEX verdadero.
*/

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    
    int t;
    cin >> t;
    vector<tuple<int, int, vector<int>>> cases;
    int n, k;
    int val;

    while (t--){
        vector<int> a;
        cin >> n >> k;
        for (long long int i = 0; i < n ; i++){
            cin >> val;
            a.push_back(val);
        }
        cases.push_back(make_tuple(n, k, a));
    }
    
    for (auto c: cases){
        n = get<0>(c);
        k = get<1>(c);
        vector<int> a = get<2>(c);

        vector<int> conteo(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int x = a[i];
            if (x <= n) {
                conteo[x]++;                                    //Creamos el arreglo de frecuencias absolutas de los enteros en la colección
            }
        }
        
        long long suma_acumulada = 0;
        int mex;
        
        for (mex = 0; mex <= n; mex++) {
            if (conteo[mex] == 0) break;                        //Desde minimo de  los enteros no negativos, determinamos MEX
            
            suma_acumulada += conteo[mex];
            
            if (suma_acumulada < 1LL * (mex + 1) * k) break;    //Determinamos si  hay suficientes elementos en la colección tal que MEX ocurra como el máximo en uno de los grupos.
        }
        
        cout << mex << endl;
    }

    return 0;
}