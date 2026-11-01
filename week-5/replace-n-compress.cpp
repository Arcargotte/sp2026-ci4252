/* Replace and Compress

    Este problema me pareció tan difícil que ahora siento que debo escribir una pequeña explicación del algoritmo que, ahora, me parece tan simple y hace lucir
    como una pérdida de tiempo las horas que invertí en resolverlo. Solo lo tomaré como experiencia para decidir con qué plan es conveniente empezar un problema
    de estos.

    Sin importar la forma inicial que tenga s: string, s puede comprimirse de tal manera que es reducida a una "forma canónica". Existen muchas formas canónicas
    que varían en forma de una base según la paridad de s, y estas formas canónicas son concatenaciones de estas formas base. Cada caracter en s tiene el potencial
    de reducir un nivel a la forma canónica anterior de la actual o de aumentarla en uno (una forma elegante de decir que podemos comprimir o expandir s), y estudiamos
    el potencial de cada caracter c en casos: X0X, X1X; cada vez que podemos aumentar la forma canónica, nos encontramos con patrones de la forma 000, 111; 
    cada vez que podemos reducirla, nos encontramos con 101 o con 010. Cualquier otro patrón mantiene la forma canónica actual que se cuenta por defecto en el algoritmo.

    Cada vez que nos conseguimos con uno de los patrones de adición o sustracción de la forma canónica, no podemos volver a sumarlo, pues estaríamos repitiendo patrones. 
    Por eso usamos las banderas para hacer la asignación de valor solo una vez: cuando nos encontramos con el patrón.

    Al final, retornamos la suma.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int replace_n_compress(string& s){
    
    int n = s.length();
    
    bool can_add = false;
    bool can_sub = false;
    
    for (int i = 1; i < n - 1; i++) {
        if (s[i-1] == s[i] && s[i] == s[i+1]) {
            can_add = true; // Existe 000 o 111. Es decir, podemos subir a una forma canónica
        }
        if (s[i-1] != s[i] && s[i-1] == s[i+1]) {
            can_sub = true; // Existe 010 o 101. Es decir, podemos reducir de la forma canónica base
        }
    }
    
    // Como tenemos al menos 3 caracteres y siempre podemos no hacer nada (comprimir), tenemos siempre cuanto menos la forma canónica base
    int ans = 1 + can_add + can_sub;
    
    return ans;
}

int main() {

    int t;
    cin >> t;
    vector<string> cases;
    string s;

    while (t--){
        cin >> s;
        cases.push_back(s);
    }
    int i = 0;

    for (string j: cases){
        cout << replace_n_compress(j) << endl;
    }

    return 0;
}