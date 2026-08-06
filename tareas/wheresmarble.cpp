#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int N, Q;
    int caseNum = 1;
    while (cin >> N >> Q && (N || Q)) {
        int marbles[N];
        for (int i = 0; i < N; i++) {
            cin >> marbles[i];
        }
        sort(marbles, marbles + N);
        cout << "CASE# " << caseNum++ << ":\n";
        while (Q--) {
            int query;
            cin >> query;
            // úsqueda binaria
            int lo = 0, hi = N - 1, pos = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (marbles[mid] == query) {
                    pos = mid;
                    hi = mid - 1; // buscar la primera ocurrencia
                } else if (marbles[mid] < query) {
                    lo = mid + 1;
                } else {
                    hi = mid - 1;
                }
            }
            if (pos == -1) {
                cout << query << " not found\n";
            } else {
                cout << query << " found at " << pos + 1 << "\n";
            }
        }
    }
    return 0;
}