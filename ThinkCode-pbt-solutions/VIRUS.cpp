/******************************************************************************
Link: VIRUS
Code: VIRUS
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-15-23.17.47
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct AhoCorasick{
    static const int CHARCNT = 2;
    static const char ORIGIN = '0';
    struct Node{
        int nxt[CHARCNT];
        int cnt;
        int link;

        Node(){
            memset(nxt, -1, sizeof nxt);
            cnt = 0;
            link = -1;
        }
    };

    vector<Node> T;

    AhoCorasick(){
        T.emplace_back();
    }

    void add(const string& s){
        int p = 0;
        for(int c: s){
            c -= ORIGIN;

            if(T[p].nxt[c] == -1){
                T[p].nxt[c] = T.size();
                T.emplace_back();
            }
            p = T[p].nxt[c];
        }

        ++T[p].cnt;
    }

    void build(){
        queue<int> que;

        T[0].link = 0;
        for(int c = 0; c < CHARCNT; ++c){
            if(T[0].nxt[c] != -1){
                T[T[0].nxt[c]].link = 0;
                que.push(T[0].nxt[c]);
            }
            else{
                T[0].nxt[c] = 0;
            }
        }

        while(!que.empty()){
            int u = que.front();
            que.pop();

            for(int c = 0; c < CHARCNT; ++c){
                int v = T[u].nxt[c];
                if(v != -1){
                    T[v].link = T[T[u].link].nxt[c];
                    T[v].cnt += T[T[v].link].cnt;
                    que.push(v);
                }
                else{
                    T[u].nxt[c] = T[T[u].link].nxt[c];
                }
            }
        }
    }

    long long Analyze(const string& Text){
        int p = 0;
        long long ans = 0;
        for(int c: Text){
            c -= ORIGIN;

            p = T[p].nxt[c];
            ans += T[p].cnt;
        }

        return ans;
    }
};

int cnt_occurrence(const string& s, const string& t){
    string X = t + '#' + s;
    int sz = X.size();

    vector<int> pi(sz);
    pi[0] = 0;

    int res = 0;
    for(int i = 1; i < sz; ++i){
        int j = pi[i - 1];
        while(j > 0 && X[i] != X[j]){
            j = pi[j - 1];
        }

        if(X[i] == X[j]){
            ++j;
        }

        pi[i] = j;
        if(j == t.size()){
            ++res;
        }
    }

    return res;
}

const int MAXN = 1e6, MAXLEN = 2e6;
int n;
pair<int, string> Data[MAXN + 5];

void subtask0(){
    vector<string> S;
    for(int i = 1; i <= n; ++i){
        if(Data[i].first == 0) S.push_back(Data[i].second);
        else{
            int ans = 0;
            for(const string& sample: S){
                ans += cnt_occurrence(Data[i].second, sample);
            }

            cout << ans << '\n';
        }
    }

}

void subtask1(){
    AhoCorasick aho;
    int i = 1;
    for(; i <= n; ++i){
        if(Data[i].first == 0) aho.add(Data[i].second);
        else{
            break;
        }
    }

    aho.build();

    for(int j = i; j <= n; ++j){
        if(Data[j].first != 1) break;

        cout << aho.Analyze(Data[j].second) << '\n';
    }
}

void input(){
    cin >> n;

    int maxLen = 0;
    for(int i = 1; i <= n; ++i){
        cin >> Data[i].first >> Data[i].second;
        if(Data[i].first == 0) maxLen = max(maxLen, (int) Data[i].second.size());
    }

    if(maxLen <= 10){
        subtask0();
    }
    else{
        subtask1();
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //freopen("VIRUS.INP","r",stdin);
    //freopen("VIRUS.OUT","w",stdout);
    input();

    return 0;
}
