#include <iostream>
using namespace std;

int a[1000006];
int b[1000006];

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;

        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];

        int i = 0, j = 0;
        int comun = 0;
        while (i < n && j < m) {
            if (a[i] == b[j]) {
                comun++;
                i++;
                j++;
            } else if (a[i] < b[j]) {
                i++;
            } else {
                j++;
            }
        }

        cout << comun << endl;
    }
    return 0;
}