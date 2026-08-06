#include <iostream>
using namespace std;

int F(int n)
{
    int dp[n + 1];
    dp[1] = 1; // caso base 1
    if (n >= 2)
        dp[2] = 1; // caso base 2
    for (int i = 3; i <= n; i++)
    {   
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int main()
{
    int n;
    cout << "Ingrese un valor de n: ";
    cin >> n;
    if (n <= 0)
    {
        cout << "Ingrese un numero positivo." << endl;
        return 0;
    }
    cout << "F(" << n << ") = " << F(n) << endl;
    return 0;
}