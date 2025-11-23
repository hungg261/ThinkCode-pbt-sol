#include<bits/stdc++.h>
using namespace std;

#define int long long

int numL[53], numR[53];
int Time = 0;
void Try(int idx, int smaller1, int larger1, int smaller2, int larger2, int less, int A, int B){
    if(idx < 0){
        if(less) cerr << ++Time << ": " << A << ' ' << B << '\n';
        return;
    }

    int bot1 = (larger1 ? 0 : numL[idx]);
    int bot2 = larger2 ? 0 : numL[idx];

    int lim1 = (smaller1 ? 9 : numR[idx]);
    int lim2 = smaller2 ? 9 : numR[idx];

//    cerr << "\t- " << A << ' ' << B << ": " << idx << ' ' << numL[idx] << ' ' << numR[idx] << " | " << bot1 << ' ' << lim1 << ' ' << bot2 << ' ' << lim2 << " | " << smaller1 << ' ' << smaller2 << " | " << larger1 << ' ' << larger2 << " | " << less << '\n';

    for(int digit1 = bot1; digit1 <= lim1; ++digit1){
        int base = less ? bot2 : max(bot2, digit1);
        for(int digit2 = base; digit2 <= lim2; ++digit2){
            Try(idx - 1,
                    (smaller1 || (digit1 < lim1)), (larger1 || (digit1 > bot1)),
                    (smaller2 || (digit2 < lim2)), (larger2 || (digit2 > bot2)),
                    (less || digit1 < digit2),
                    A * 10 + digit1, B * 10 + digit2);
        }
    }
}

void solve(int L, int R){
    int lenL = 0, lenR = 0;

    int tmpL = L, tmpR = R;
    while(tmpL > 0){
        numL[lenL++] = tmpL % 10;
        tmpL /= 10;
    }

    while(tmpR > 0){
        numR[lenR++] = tmpR % 10;
        tmpR /= 10;
    }

    int len = max(lenL, lenR);

    Try(len - 1, 0, 0, 0, 0, 0, 0, 0);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int L, R;
    cin >> L >> R;

    solve(L, R);


    return 0;
}
