#include <iostream>
using namespace std;

int main() {
    int attempts[26] = {0};
    bool solved[26] = {false};
    int solvedTime[26] = {0};

    while (true) {
        int m;
        cin >> m;
        if (m == -1) break;

        char prob;
        char result[10];
        cin >> prob >> result;

        int idx = prob - 'A';

        if (solved[idx]) continue;

        if (result[0] == 'r') {
            solved[idx] = true;
            solvedTime[idx] = m + 20 * attempts[idx];
        } else {
            attempts[idx]++;
        }
    }

    int count = 0;
    int total = 0;
    for (int i = 0; i < 26; i++) {
        if (solved[i]) {
            count++;
            total += solvedTime[i];
        }
    }

    cout << count << " " << total << endl;

    return 0;
}