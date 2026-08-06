#include <iostream>
using namespace std;

int a[200005];
int temp[200005];
long long contador = 0;

void mezclar(int l, int r) {
    if (l >= r) return;

    int mid = (l + r) / 2;
    mezclar(l, mid);
    mezclar(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
            contador += (mid - i + 1);
        }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= r) temp[k++] = a[j++];

    for (int x = l; x <= r; x++) a[x] = temp[x];
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    mezclar(0, n - 1);

    cout << contador << endl;
    return 0;
}