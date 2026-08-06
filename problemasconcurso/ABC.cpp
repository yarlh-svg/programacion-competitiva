#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;

    int mn, md, mx;

    if (a <= b && a <= c) {
        mn = a;
        if (b <= c) { md = b; mx = c; }
        else { md = c; mx = b; }
    } else if (b <= a && b <= c) {
        mn = b;
        if (a <= c) { md = a; mx = c; }
        else { md = c; mx = a; }
    } else {
        mn = c;
        if (a <= b) { md = a; mx = b; }
        else { md = b; mx = a; }
    }

    char pattern[4];
    cin >> pattern;

    for (int i = 0; i < 3; i++) {
        if (pattern[i] == 'A') cout << mn;
        else if (pattern[i] == 'B') cout << md;
        else cout << mx;

        if (i < 2) cout << " ";
    }
    cout << endl;

    return 0;
}