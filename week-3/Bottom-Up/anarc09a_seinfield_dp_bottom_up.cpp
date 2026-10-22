/*
    ANARC09A - Seinfield

    Con programación dinámica (DP) - Bottom-Up

    Originalmente la resolución de este problema fue escrito con Python, pero como SPOJ daba el código TLE se tradució
    la solución a CPP para mejorar el tiempo de ejecución.

    Aquí, implementamos una solución Bottom-Up definiendo a dp[i][bal] como el string s de tamaño i, con 0<=i<=n-1 con un
    balance bal que cuenta la cantidad de llaves abiertas en s, que definimos como bal = count('{') - count('}') y cuyo valor
    sinboliza la cantidad minima de movimientos que hay que hacer para que s sea balanceado habiendo recorrido hasta la 
    i-ésima posición de s.

    La respuesta del problema se consigue en la casilla dp[n][0].

    Partimos del caso base dp[0][0] = 0 y construimos la solución preguntándonos los costos de las operaciones anteriores
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string case_str;
    int case_num = 1;

    while (cin >> case_str) {
        if (case_str.find('-') != string::npos) {
            break;
        }

        int n = case_str.length();
        // Aquí evitamos definir una matriz para recordar los valores en cada fila
        vector<int> dp(n + 1, INF);
        dp[0] = 0;

        for (int row = 0; row < n; ++row) {
            char ch = case_str[row];
            // Y aquí calculamos la siguiente fila
            vector<int> next_dp(n + 1, INF);

            int costo_open = (ch == '{') ? 0 : 1;
            int costo_close = (ch == '}') ? 0 : 1;

            for (int bal = 0; bal <= row; ++bal) {
                if (dp[bal] == INF) continue;

                next_dp[bal + 1] = min(next_dp[bal + 1], dp[bal] + costo_open);

                if (bal > 0) {
                    next_dp[bal - 1] = min(next_dp[bal - 1], dp[bal] + costo_close);
                }
            }

            dp = next_dp;
        }

        cout << case_num << ". " << dp[0] << "\n";
        case_num++;
    }

    return 0;
}