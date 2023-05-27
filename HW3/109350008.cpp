#include <iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    long long** dp = new long long*[n + 1];
    int** profit = new int*[n + 1];
    for (int i = 0; i <= n; i++) dp[i] = new long long[m + 1];
    for (int i = 0; i < n; i++) profit[i] = new int[m + 1];


    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            cin >> profit[i][j];

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dp[i][j] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j]; //last best

            for (int k = 0; k <= j; k++)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + profit[i - 1][k]); //update
        }
    
    /*
    cout << "allocation result:\n";
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
            printf("%2d ", dp[i][j]);
        cout << endl;
    }
    cout << "\n\n";
    */

    cout << dp[n][m] << endl;

}


/*
4 6
0 4 6 7 7 7 7
0 2 4 6 8 9 10
0 6 8 8 8 8 8
0 2 3 4 4 4 4
*/