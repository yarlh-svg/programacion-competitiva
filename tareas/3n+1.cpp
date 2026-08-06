#include <iostream>
using namespace std;

int main() {
    int inicio, fin, max_pasos = 0;
    cin >> inicio >> fin;
    
    // Recorrer cada número en el rango
    for(int numero = inicio; numero <= fin; numero++) {
        int n = numero;
        int pasos = 0;
        
        while(n != 1) {
            if(n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
            pasos++;
        }
                if(pasos > max_pasos) {
            max_pasos = pasos;
        }
    }
    
    cout << max_pasos << endl;
    return 0;
}