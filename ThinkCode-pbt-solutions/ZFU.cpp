/******************************************************************************
Link: ZFU
Code: ZFU
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-16-13.58.02
*******************************************************************************/
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MAXN = 1e6;
const int BASE = 37, MOD = 1e9 + 23;
int hashes[MAXN + 5], powhash[MAXN + 5];

string S;
int n;
int Q;
int Z[MAXN + 5], maxsuf[MAXN + 5];

void compute(){
    powhash[0] = 1;
    for(int i = 1; i <= n; ++i){
        hashes[i] = (hashes[i - 1] * BASE + (S[i] - 'a' + 1)) % MOD;
        powhash[i] = powhash[i - 1] * BASE % MOD;
    }
}

int getHash(int l, int r){
    return ((hashes[r] - hashes[l - 1] * powhash[r - l + 1] % MOD) % MOD + MOD) % MOD;
}

void Zfunction(){
    for(int i = 1; i <= n; ++i){
        int l = 1, r = n - i + 1, res = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(getHash(i, i + mid - 1) == getHash(1, mid)){
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        Z[i] = res;
    }

    maxsuf[n] = Z[n];
    for(int i = n - 1; i >= 1; --i){
        maxsuf[i] = max(maxsuf[i + 1], Z[i]);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("ZFU.INP","r",stdin);
    //freopen("ZFU.OUT","w",stdout);
    cin >> S;
    n = S.size();
    S = '#' + S;

    compute();
    Zfunction();

    cin >> Q;
    while(Q--){
        int i;
        cin >> i;

        cout << maxsuf[i] << '\n';
    }

    return 0;
}
