/******************************************************************************
Link: CPMT
Code: CPMT
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-23-23.02.13
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

const int MAX = 200, MAXLG = __lg(MAX) + 1;
int arr[MAX + 1][MAX + 1];
int table[MAX + 1][MAX + 1][MAXLG + 1];
int table_2d[MAX * (MAX + 1) / 2][MAX + 1][MAXLG + 1];
int pref[MAX + 1][MAX + 1];
int n, m;

int id(int l, int r){
    return (l > 1 ? (n - (l - 1) + 1 + n) * (l - 1) / 2 : 0) + (r - l + 1);
}

int queryGCD(int col, int l, int r){
    int bit = __lg(r - l + 1);
    return __gcd(table[col][l][bit], table[col][r - (1 << bit) + 1][bit]);
}

int queryGCD_2d(int l, int r, int u, int v){
    int bit = __lg(v - u + 1);
    return __gcd(table_2d[id(l, r)][u][bit], table_2d[id(l, r)][v - (1 << bit) + 1][bit]);
}

void compute(){
    for(int j = 1; j <= m; ++j){
        for(int i = 1; i <= n; ++i){
            pref[j][i] = pref[j][i - 1] + arr[i][j];
        }
    }

    for(int j = 1; j <= m; ++j){
        for(int i = 1; i <= n; ++i){
            table[j][i][0] = arr[i][j];
        }

        for(int k = 1; k <= MAXLG; ++k){
            for(int i = 1; i <= n; ++i){
                table[j][i][k] = __gcd(table[j][i][k - 1], table[j][i + (1 << (k - 1))][k - 1]);
            }
        }
    }

    for(int l = 1; l <= n; ++l){
        for(int r = l; r <= n; ++r){
            for(int j = 1; j <= m; ++j){
                table_2d[id(l, r)][j][0] = queryGCD(j, l, r);
            }

            for(int k = 1; k <= MAXLG; ++k){
                for(int j = 1; j <= m; ++j){
                    table_2d[id(l, r)][j][k] = __gcd(table_2d[id(l, r)][j][k - 1], table_2d[id(l, r)][j + (1 << (k - 1))][k - 1]);
                }
            }
        }
    }
}


void solve(){
    long long ans = 1e18;
    for(int i = 1; i <= n; ++i){
        for(int j = i; j <= n; ++j){
            int l = 1;
            long long sum = 0;
            for(int r = 1; r <= m; ++r){
                sum += pref[r][j] - pref[r][i - 1];
                while(l <= r && queryGCD_2d(i, j, l, r) == 1){
                    ans = min(ans, sum);

                    sum -= pref[l][j] - pref[l][i - 1];
                    ++l;
                }
            }
        }
    }

    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("CPMT.INP","r",stdin);
    //freopen("CPMT.OUT","w",stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            cin >> arr[i][j];
        }
    }

    compute();
    solve();

    return 0;
}
