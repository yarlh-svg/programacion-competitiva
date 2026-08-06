#include <iostream>
using namespace std;

int main() {
    char s[205];
    cin >> s;

    int len = 0;
    while (s[len] != '\0') len++;

    int scoreA = 0, scoreB = 0;

    for (int i = 0; i < len; i += 2) {
        char player = s[i];
        int pts = s[i + 1] - '0';

        if (player == 'A') scoreA += pts;
        else scoreB += pts;
    }

    if (scoreA > scoreB) cout << "A" << endl;
    else cout << "B" << endl;

    return 0;
}