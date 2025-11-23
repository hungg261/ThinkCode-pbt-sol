/******************************************************************************
Link: EGGS
Code: EGGS
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-22-22.29.32
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

#define int long long

const int OFFSET = 4240;
int dp[53][2][2][2][2][2][8485];
int numL[53], numR[53];
int Try(int idx, int smaller1, int larger1, int smaller2, int larger2, int less, int diff){
    if(idx < 0) return less && diff > OFFSET;

    int& memo = dp[idx][smaller1][larger1][smaller2][larger2][less][diff];
    if(memo != -1) return memo;

    int bot1 = larger1 ? 0 : numL[idx];
    int bot2 = larger2 ? 0 : numR[idx];

    int lim1 = smaller1 ? 80 : numL[idx];
    int lim2 = smaller2 ? 80 : numR[idx];

    memo = 0;
    for(int digit1 = bot1; digit1 <= lim1; ++digit1){
        int base = max(bot2, (less ? 0 : digit1));
        for(int digit2 = base; digit2 <= lim2; ++digit2){
            memo += Try(idx - 1,
                        (smaller1 || (digit1 < lim1)), (larger1 || (digit1 > bot1)),
                        (smaller2 || (digit2 < lim2)), (larger2 || (digit2 > bot2)),
                        (less || (digit1 < digit2)),
                        diff + (digit1 - digit2));
        }
    }

    return memo;
}

int solve(int L, int R){
    int lenL = 0, lenR = 0;

    int tmpL = L, tmpR = R;
    while(tmpL > 0){
        numL[lenL++] = tmpL % 81;
        tmpL /= 81;
    }

    while(tmpR > 0){
        numR[lenR++] = tmpR % 81;
        tmpR /= 81;
    }
`
    int len = max(lenL, lenR);

    memset(dp, -1, sizeof dp);
    return Try(len - 1, 0, 0, 0, 0, 0, OFFSET);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("EGGS.INP","r",stdin);
    //freopen("EGGS.OUT","w",stdout);
    int L, R;
    cin >> L >> R;

    cout << solve(L, R) << '\n';

    return 0;
}
