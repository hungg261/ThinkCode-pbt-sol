/******************************************************************************
Link: MNUM
Code: MNUM
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-13-13.22.27
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

int k;
int POW10[20];

void compute(){
    POW10[0] = 1;
    for(int i = 1; i <= 16; ++i){
        POW10[i] = POW10[i - 1] * 10;
    }
}

string toString(int n){
    string res;
    while(n > 0){
        res += n % 10 + '0';
        n /= 10;
    }
    reverse(begin(res), end(res));
    return res;
}

int cntLength(int n){
    int res = 0;

    int d = 1;
    while(n > 9 * POW10[d - 1]){
        res += d * 9 * POW10[d - 1];
        n -= 9 * POW10[d - 1];
        ++d;
    }

    res += d * n;
    return res;
}

int solve(int n){
    if(n <= 1) return 1;
    else if(n <= 5) return 2;

    int length = cntLength(n);
    int idx = 2, bitlen = 2;

    while(idx <= length){
        idx = (1LL << bitlen) + idx;

        bitlen += 2;
    }
    for(int bit = 60; bit >= 0; --bit){
        if(idx >> bit & 1){
            idx ^= 1LL << bit;
            break;
        }
    }

    long long luythua10 = 1;
    int so_chu_so = 1;

    long long di_qua = 0;
    while(idx > 9 * luythua10 * so_chu_so){
        idx -= 9 * luythua10 * so_chu_so;
        di_qua += 9 * luythua10;

        ++so_chu_so;
        luythua10 *= 10;
    }

    long long owner = di_qua + (idx + so_chu_so - 1) / so_chu_so;
    int fixed_index = (idx + so_chu_so - 1) % so_chu_so;

    return toString(owner)[fixed_index] - '0';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("MNUM.INP","r",stdin);
    //freopen("MNUM.OUT","w",stdout);

    compute();

    cin >> k;
    while(k--){
        int n;
        cin >> n;

        cout << solve(n);
    }

    return 0;
}
