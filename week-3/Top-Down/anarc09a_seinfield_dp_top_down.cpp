/*
    ANARC09A - Seinfield

    Con programación dinámica (DP) - Top-Down

    Aquí definimos los sub-problemas de forma similar a la estrategia Bottom-Up, pero siguiendo esta estrategia
    usamos la tabla de memorización y llamamos recursivamente a solve que consulta en la tabla valores previamente calculados
    o computa los valores correspondientes a cada nodo del árbol de soluciones recorriendo la ramas generadas con los llamados
    a solve en la asignación de op1 y op2
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

// La tabla de memorización se inicializa con una dimensión constante grande para responder cualquier problema
int memo[2005][2005];
string case_str;
int n;

int solve(int i, int bal) {
    if (i == n) return (bal == 0) ? 0 : INF;
    if (memo[i][bal] != -1) return memo[i][bal];

    int op1 = (case_str[i] == '{' ? 0 : 1) + solve(i + 1, bal + 1);
    int op2 = INF;
    if (bal > 0) op2 = (case_str[i] == '}' ? 0 : 1) + solve(i + 1, bal - 1);

    return memo[i][bal] = min(op1, op2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int i = 1;
    while (cin >> case_str) {
        if (case_str.find('-') != string::npos) {
            break;
        }

        // Reiniciamos la tabla de memorización por cada caso a resolver.
        n = case_str.length();
        for(int i = 0; i <= n; ++i){
            for(int j = 0; j <= n; ++j){
                memo[i][j] = -1;
            }
        }

        cout << i << ". " << solve(0, 0) << "\n";
        i++;
    }

    return 0;
}
