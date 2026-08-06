#include <iostream> 
using namespace std; 
int board[8][8]; 
bool col[8], diag1[15], diag2[15]; 
int maxScore; 

void solve(int row, int currentSum) { 
    if (row == 8) { 
        if (currentSum > maxScore) 
            maxScore = currentSum; 
        return; 
    } 
    for (int j = 0; j < 8; j++) { 
        int d1 = row- j + 7; 
        int d2 = row + j; 
        if (!col[j] && !diag1[d1] && !diag2[d2]) { 
            col[j] = diag1[d1] = diag2[d2] = true; 
            solve(row + 1, currentSum + board[row][j]); 
            col[j] = diag1[d1] = diag2[d2] = false; 
        } 
    } 
} 

int main() { 
    int k; 
    cin >> k; 
    while (k--) { 
        for (int i = 0; i < 8; i++) 
            for (int j = 0; j < 8; j++) 
                cin >> board[i][j]; 
        for (int i = 0; i < 8; i++) 
            col[i] = false; 
        for (int i = 0; i < 15; i++) 
            diag1[i] = diag2[i] = false; 
        maxScore = 0; 
        solve(0, 0); 
        cout << maxScore << "\n"; 
    } 
    return 0; 
}