/**
 *      Polymul
 *      
 *      El programa aquí escrito es una adaptación del ilustrado en
 *      "Algorithms for Competitive Programming" en el artículo 
 *      "Fast Fourier Transform" para que el juez online SPOJ pueda 
 *      aceptarlo como solución al problema Polynum. Los comentarios 
 *      en este programa son dedicados a explicar el razonamiento
 *      detrás del algoritmo que retorna el producto de dos polinomios
 *      en tiempo O(n log n).
 * 
 *      Para retornar el producto de dos polinomios nos aprovechamos
 *      de su representación puntual: dados n puntos x_i, con 0<=i<n,
 *      evaluamos el polinomio p en x_i tal que la n-tupla de la forma
 *      (p(x_0), ..., p(x_n-1)) representa de forma única a p. Así,
 *      el producto polinomial p * q lo representa la tupla
 *      (p(x_0) * q(x_0'), ..., p(x_2n) * q(x_2n')), que se resuelve
 *      con complejidad O(n). De aquí, el problema radica en obtener
 *      los coeficientes del producto polinomial. Inicialmente, 
 *      tenemos la ecuación matricial
 * 
 *                                 M * A = p
 * 
 *      Donde M es la matriz cuya i-ésima fila tiene la forma
 *                          
 *                            1 x_i x_i^2 ... x_i^n
 *      
 *      Y M es una matriz de Vandermonde.
 *      A es el vector de coeficientes y p es el vector p(x_i).
 *      Para obtener los coeficientes, resolvemos A = p * M^-1,
 *      que es O(n^2) (que llamaremos interpolación). Al final,
 *      el algoritmo debería seguir teniendo complejidad O(n^2).
 *      
 *      Para mejorar el tiempo, aplicamos la Transformada Discreta
 *      de Fourier, que evalua un polinomio de grado n en las
 *      n-ésimas raíces de 1 de la forma w=e^((2pi/n)*i). Y dividimos
 *      el polinomio en dos: uno que tiene los coeficientes para
 *      exponentes pares y el otro para los coeficientes de
 *      exponentes impares, tal que ambos tengan grado n/2 - 1 y 
 *      así reexpresar p de la forma p(x)=p_par(x^2)+x*p_impar(x^2)
 *      (al que llamamos DFT)
 *      
 *      Con una estrategia dividr y conquistar, el algoritmo FFT
 *      define un arreglo de representación puntual de p "reutilizando"
 *      operaciones aprovechándose de la identidad de que
 *      p(x)=p_par(x^2)+x*p_impar(x^2) y p(-x)=p_par(x^2)-x*p_impar(x^2),
 *      y así, usando una raíz de la unidad, calcula n puntos usando
 *      las primeras n/2 raíces y, como las otras n/2 están a un ángulo pi
 *      de diferencia del círculo unitario complejo, las calcula con la 
 *      expresión (-1) * w^j. FFT tiene una complejidad O(nlogn).
 * 
 *      Retomando el problema de hallar M^-1, notamos que la inversa es \
 *      equivalente a hallar otra DFT con raíz w^-1 y dividir la matriz
 *      resultante por n. De aquí, queda hacer la multiplicación de
 *      polinomios en representación puntual de la que hablamos en un
 *      principio, que es O(n). Y como O(n) + O(nlogn) = O(nlogn), al final, 
 *      quedamos con un algoritmo de multiplicación de polinomios con 
 *      complejidad O(nlogn).
 *      
 */

#include <iostream>
#include <complex>
#include <vector>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);


void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    // la k-ésima raíz de la unidad
    double ang = 2 * PI / n * (invert ? -1 : 1);
    // representación de complejo en forma cis
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; i++)
        // Tomamos la parte real del i-ésimo 
        // coeficiente, pero convertimos en real
        // porque va a existir un error imaginario
        // de la forma 0.0...i. Luego, redondeamos.
        result[i] = round(fa[i].real());
    return result;
}


int main() {
    
    int T;

    if (cin >> T) {
        while (T--) {
            int n;
            cin >> n;

            vector<long long> A(n + 1);
            vector<long long> B(n + 1);

            for (int i = 0; i <= n; ++i) {
                cin >> A[i];
            }

            for (int i = 0; i <= n; ++i) {
                cin >> B[i];
            }

            vector<long long> result = multiply(A, B);
            for (int i = 0; i <= 2 * n; ++i) {
                cout << result[i] << (i == 2 * n ? "\n" : " ");
            }           
        }
    }
    return 0;
}