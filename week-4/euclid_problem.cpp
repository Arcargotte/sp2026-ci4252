/*
    UVA - Euclid's Problem

    Para este ejercicio se implementó el algoritmo de euclides extendido para retornar el máximo común divisor entre enteros a y b, que llamamos g, y el par (x, y) con 
    los mínimos x y y tales que se cumple la ecuación diofántica 

    a * x + b * c = g

    Este algoritmo se aprovecha de la coincidencia de los divisores del par (a, b) y (a, a - b) del algoritmo de euclides clásico y busca escribir g ccomo
    una combinación lineal de a y b para enteros x y y. Para encontrar el par (x, y), partimos de los coeficientes (1, 0) cuando b = 0 y a = g y aprovechamos
    de la identidad de que x = y_1 y y = x_1 - y_1 * floor(a / b) y que retornamos en forma de referencia después de haber conseguido g.

*/

#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int main(){
    
    int A;
    int B;
    vector<vector<int>> cases;

    while (cin >> A >> B){
        cases.push_back({A, B});
    }

    for (vector<int> pair: cases){
        int x;
        int y;
        int d = gcd(pair[0], pair[1], x, y);

        cout << x << " " << y << " " << d << endl;
    }
    
    return 0;
}