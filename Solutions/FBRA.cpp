#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 500;
const int MOD = 1e9 + 7;
int dp[MAXN + 5][MAXN + 5];
string S;
int n;

bool match(char o, char c){
    if(o == '(' && c == ')') return true;
    else if(o == '[' && c == ']') return true;
    else if(o == '{' && c == '}') return true;
    else if(o == '?' && c == ')') return true;
    else if(o == '(' && c == '?') return true;
    else if(o == '?' && c == ']') return true;
    else if(o == '[' && c == '?') return true;
    else if(o == '?' && c == '}') return true;
    else if(o == '{' && c == '?') return true;
    return false;
}

bool freestyle(char o, char c){
    return o == '?' && c == '?';
}

bool connected(char o, char c){
    return match(o, c) || freestyle(o, c);
}

void solve(){
    for(int i = 1; i <= n + 1; ++i){
        dp[i][i - 1] = 1;
    }
    for(int i = 2; i <= n; ++i){
        int& ways = dp[i - 1][i];
        if(match(S[i - 1], S[i])) ways = 1;
        else if(freestyle(S[i - 1], S[i])) ways = 3;
    }

    for(int len = 4; len <= n; len += 2){
        for(int i = 1; i + len - 1 <= n; ++i){
            int j = i + len - 1;

            for(int k = i + 1; k <= j; k += 2){
                int ways = 0;
                if(match(S[i], S[k])) ways = 1;
                else if(freestyle(S[i], S[k])) ways = 3;

                dp[i][j] += ways * dp[i + 1][k - 1] % MOD * dp[k + 1][j] % MOD;
                dp[i][j] %= MOD;
            }
        }
    }

//    for(int len = 2; len <= n; len += 2){
//        for(int i = 1; i + len - 1 <= n; ++i){
//            int j = i + len - 1;
//
//            cerr << i << ' ' << j << ": " << dp[i][j] << '\n';
//            for(int k = i + 1; k <= j; k += 2){
//                cerr << "\t" << i << ' ' << k << ": " << S[i] << ' ' << S[k] << '\n';
//            }
//        }
//    }

//    cerr << dp[3][6] << '\n';
    cout << dp[1][n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> S;
    n = S.size();
    S = '#' + S;

    solve();

    return 0;
}
