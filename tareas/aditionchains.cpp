#include <iostream>
#include <fstream>

//Yarin Nilo Laqui Huilahuaña
//Anderson Leonardo Flores Macedo
//Gabriel Anderson Ramos Jahuira
using namespace std;

int cadena[100];
int n;
bool solucion_encontrada;

void buscar_cadena(int k, int m) {
        if (k == m) {
        if (cadena[m] == n) {
            solucion_encontrada = true;
        }
        return;
    }

    for (int i = k; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {

            int suma = cadena[i] + cadena[j];
            if (suma > cadena[k] && suma <= n) {
                cadena[k + 1] = suma;
                buscar_cadena(k + 1, m);
                if (solucion_encontrada) return;
            }
        }
    }
}

int main() {

    ifstream archivo("entrada.txt");

    if (!archivo.is_open()) {
        cout << "Error:" << endl;
        return 1;
    }
    while (archivo >> n && n != 0) {

        cadena[0] = 1;
        solucion_encontrada = false;
        int m = 0;
        while (!solucion_encontrada) {
            buscar_cadena(0, m);
            if (solucion_encontrada) {
                for (int paso = 0; paso <= m; paso++) {
                    cout << cadena[paso] << (paso == m ? "" : " ");
                }
                cout << endl;
            }

            m++;
        }
    }

    archivo.close();
    return 0;
}