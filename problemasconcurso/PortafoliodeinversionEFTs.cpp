#include <iostream>
using namespace std;

int C, N;
int p[20];
long long contador = 0;

void buscar(int idx, int suma) {
    if (idx == N) {
        if (suma == C) contador++;
        return;
    }
    buscar(idx + 1, suma + p[idx]);
    buscar(idx + 1, suma);
}

int main() {
    cin >> C >> N;
    for (int i = 0; i < N; i++) cin >> p[i];

    buscar(0, 0);

    cout << contador << endl;
    return 0;
}