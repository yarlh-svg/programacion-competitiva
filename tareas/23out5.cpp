#include <iostream>
#include <algorithm>
using namespace std;

int apply(int a, int b, int op) {
    if (op == 0) return a + b;
    if (op == 1) return a - b;
    return a * b;
}

int main() {
    int a[5];
    while (cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4]) {
        if (a[0] == 0 && a[1] == 0 && a[2] == 0 && a[3] == 0 && a[4] == 0) break;
        sort(a, a + 5);
        bool found = false;
        do {
            for (int o1 = 0; o1 < 3 && !found; o1++)
                for (int o2 = 0; o2 < 3 && !found; o2++)
                    for (int o3 = 0; o3 < 3 && !found; o3++)
                        for (int o4 = 0; o4 < 3 && !found; o4++) {
                            int r = apply(a[0], a[1], o1);
                            r = apply(r, a[2], o2);
                            r = apply(r, a[3], o3);
                            r = apply(r, a[4], o4);
                            if (r == 23) found = true;
                        }
        } while (!found && next_permutation(a, a + 5));
        cout << (found ? "Possible" : "Impossible") << "\n";
    }
    return 0;
}