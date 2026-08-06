#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.ignore();

    char prefix[] = "Simon says ";
    int prefixLen = 11;

    for (int i = 0; i < n; i++) {
        char line[105];
        cin.getline(line, 105);

        int lineLen = 0;
        while (line[lineLen] != '\0') lineLen++;

        bool matches = (lineLen >= prefixLen);
        if (matches) {
            for (int j = 0; j < prefixLen; j++) {
                if (line[j] != prefix[j]) {
                    matches = false;
                    break;
                }
            }
        }

        if (matches) {
            for (int j = prefixLen; j < lineLen; j++) {
                cout << line[j];
            }
            cout << endl;
        }
    }

    return 0;
}