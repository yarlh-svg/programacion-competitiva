#include <iostream>
using namespace std;

char grid[1005][1005];
bool visitado[1005][1005];
int pilaI[1000006], pilaJ[1000006];
int R, C;

void explorar(int si, int sj) {
    int tope = 0;
    pilaI[tope] = si;
    pilaJ[tope] = sj;
    tope++;
    visitado[si][sj] = true;

    while (tope > 0) {
        tope--;
        int i = pilaI[tope];
        int j = pilaJ[tope];

        int di[4] = {-1, 1, 0, 0};
        int dj[4] = {0, 0, -1, 1};

        for (int d = 0; d < 4; d++) {
            int ni = i + di[d];
            int nj = j + dj[d];
            if (ni >= 0 && ni < R && nj >= 0 && nj < C && grid[ni][nj] == '1' && !visitado[ni][nj]) {
                visitado[ni][nj] = true;
                pilaI[tope] = ni;
                pilaJ[tope] = nj;
                tope++;
            }
        }
    }
}

int main() {
    cin >> R >> C;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            cin >> grid[i][j];

    int islas = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '1' && !visitado[i][j]) {
                islas++;
                explorar(i, j);
            }
        }
    }

    cout << islas << endl;
    return 0;
}