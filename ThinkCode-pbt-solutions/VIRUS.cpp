/******************************************************************************
Link: VIRUS
Code: VIRUS
Time (YYYY-MM-DD-hh.mm.ss): 2025-11-15-23.17.47
*******************************************************************************/
#include<bits/stdc++.h>
using namespace std;

struct AhoCorasick{
    struct Node{
        int nxt[2];
        int link;
        int occurrences;
        vector<int> ends;

        Node(){
            memset(nxt, -1, sizeof nxt);
            occurrences = 0;
            link = -1;
        }
    };

    vector<Node> T;
    vector<vector<int>> adj;
    int root;

    AhoCorasick(){
        T.emplace_back();
        root = 0;
    }

    void add(int idx, const string& s){
        int p = root;
        for(int c: s){
            c -= '0';

            if(T[p].nxt[c] == -1){
                T[p].nxt[c] = T.size();

                T.emplace_back();
            }
            p = T[p].nxt[c];
        }

        T[p].ends.push_back(idx);
    }

    void construct(){
        T[root].link = root;
        queue<int> que;

        for(int c = 0; c < 2; ++c){
            int v = T[root].nxt[c];
            if(v != -1){
                T[v].link = root;
                que.push(v);
            }
            else{
                T[root].nxt[c] = root;
            }
        }

        while(!que.empty()){
            int u = que.front();
            que.pop();

            for(int c = 0; c < 2; ++c){
                int v = T[u].nxt[c];
                if(v != -1){
                    T[v].link = T[T[u].link].nxt[c];
                    que.push(v);
                }
                else{
                    T[u].nxt[c] = T[T[u].link].nxt[c];
                }
            }
        }

        adj.resize(T.size());
        for(int i = 1; i < T.size(); ++i){
            adj[T[i].link].push_back(i);
        }
    }

    int dfs(int u, vector<int>& res){
        int occ = T[u].occurrences;
        for(int v: adj[u]){
            occ += dfs(v, res);
        }

        for(int id: T[u].ends){
            res[id] = occ;
        }

        return occ;
    }

    void AddSearchText(const string& Text){
        int p = root;
        for(int c: Text){
            c -= '0';

            p = T[p].nxt[c];
            if(p != -1){
                T[p].occurrences++;
            }
        }
    }

    void RemoveSearchText(const string& Text){
        int p = root;
        for(int c: Text){
            c -= '0';

            p = T[p].nxt[c];
            if(p != -1){
                T[p].occurrences--;
            }
        }
    }

    void Search(vector<int>& res){
        dfs(root, res);
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
    int i = 1, cnt = 0;
    for(; i <= n; ++i){
        if(Data[i].first == 0) aho.add(cnt++, Data[i].second);
        else{
            break;
        }
    }

    aho.construct();

    vector<int> res(cnt);
    for(int j = i; j <= n; ++j){
        aho.AddSearchText(Data[j].second);


        aho.Search(res);
        cout << accumulate(begin(res), end(res), 0LL) << '\n';

        aho.RemoveSearchText(Data[j].second);
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
