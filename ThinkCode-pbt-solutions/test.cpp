#include<bits/stdc++.h>
using namespace std;

#define int long long

struct BigBin {
    string s;

    BigBin() : s("0") {}
    BigBin(const string &x) {
        int p = 0;
        while (p + 1 < (int)x.size() && x[p] == '0') p++;
        s = x.substr(p);
    }

    static BigBin fromInt(long long x) {
        if (x == 0) return BigBin("0");
        string r;
        while (x > 0) {
            r.push_back(char('0' + (x & 1)));
            x >>= 1;
        }
        reverse(r.begin(), r.end());
        return BigBin(r);
    }

    static BigBin fromDecimal(string dec) {
        while (dec.size() > 1 && dec[0] == '0') dec.erase(dec.begin());
        if (dec == "0") return BigBin("0");

        string r;
        while (!(dec.size() == 1 && dec[0] == '0')) {
            int carry = 0;
            for (int i = 0; i < (int)dec.size(); i++) {
                int x = carry * 10 + (dec[i] - '0');
                dec[i] = char('0' + (x / 2));
                carry = x & 1;
            }
            r.push_back(char('0' + carry));
            while (dec.size() > 1 && dec[0] == '0') dec.erase(dec.begin());
        }
        reverse(r.begin(), r.end());
        return BigBin(r);
    }


    void norm() {
        int p = 0;
        while (p + 1 < (int)s.size() && s[p] == '0') p++;
        s = s.substr(p);
    }

    static int cmp(const BigBin &a, const BigBin &b) {
        if (a.s.size() != b.s.size()) return a.s.size() < b.s.size() ? -1 : 1;
        if (a.s == b.s) return 0;
        return a.s < b.s ? -1 : 1;
    }

    BigBin operator+(const BigBin &o) const {
        string a = s, b = o.s;
        int i = a.size()-1, j = b.size()-1, carry = 0;
        string r;
        while (i >= 0 || j >= 0 || carry) {
            int x = carry;
            if (i >= 0) x += a[i--]-'0';
            if (j >= 0) x += b[j--]-'0';
            r.push_back(char('0' + (x&1)));
            carry = x >> 1;
        }
        reverse(r.begin(), r.end());
        return BigBin(r);
    }

    BigBin operator-(const BigBin &o) const {
        if (cmp(*this, o) < 0) return BigBin("0");
        string a = s, b = o.s;
        int i = a.size()-1, j = b.size()-1, borrow = 0;
        string r;
        while (i >= 0) {
            int x = (a[i]-'0') - borrow;
            if (j >= 0) x -= (b[j--]-'0');
            if (x < 0) { x += 2; borrow = 1; }
            else borrow = 0;
            r.push_back(char('0' + x));
            i--;
        }
        while (r.size() > 1 && r.back()=='0') r.pop_back();
        reverse(r.begin(), r.end());
        return BigBin(r);
    }

    BigBin operator<<(int k) const {
        if (s == "0") return *this;
        return BigBin(s + string(k, '0'));
    }

    BigBin operator>>(int k) const {
        if ((int)s.size() <= k) return BigBin("0");
        return BigBin(s.substr(0, s.size()-k));
    }

    BigBin getLastK(int k) const {
        if ((int)s.size() <= k) return *this;
        return BigBin(s.substr(s.size()-k));
    }

    int modInt(int m) const {
        long long r = 0;
        for (char c : s) r = ((r<<1) + (c-'0')) % m;
        return r;
    }
};

const int MAXBIT = 3322;
const int MOD = 1e9 + 7;

int solve(const BigBin& N, int bitpos){
    BigBin rep = N >> (bitpos + 1);
    BigBin cnt = rep << bitpos;

    return (cnt + (N.getLastK(bitpos + 1) - ((BigBin("1") << bitpos) - BigBin("1")))).modInt(MOD);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    string _n, _m;
    cin >> _n >> _m;

    BigBin n = BigBin::fromDecimal(_n), m = BigBin::fromDecimal(_m);
    int mod_n = n.modInt(MOD), mod_m = m.modInt(MOD);
    n = n - BigBin("1");
    m = m - BigBin("1");

    int ans = 0;
    for(int bit = MAXBIT; bit >= 0; --bit){
        int bit1_n = solve(n, bit),
            bit1_m = solve(m, bit);

        int cnt = (1LL * bit1_n * (mod_m - bit1_m) % MOD + 1LL * (mod_n - bit1_n) * bit1_m % MOD) % MOD;

        ans = (ans + 1LL * cnt * ((BigBin("1") << bit).modInt(MOD)) % MOD) % MOD;
    }

    cout << (ans + MOD) % MOD << '\n';

    return 0;
}
