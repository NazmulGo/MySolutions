//primes = {285897553, 745494041, 693888673, 950758511, 282174533, 847345579, 722520917, 354688703, 963459817, 139793893};
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vll vector<ll>
#define pll pair<ll, ll>
#define endl "\n" 
#define all(v) v.begin(), v.end()
#define fr(x, n) for (int i = x; i < n; ++i)

const int N = 1e6+12;
const int b1 = 137, b2 = 277;
const int M1 = 1e9+7, M2 = 139793893;
pair<int, int> pw[N], ipw[N], pref[N];


ll big_mod(ll a, ll b, ll mod) {
   ll ans = 1;
   while(b) {
   if(b & 1) ans = (ans * a) % mod;
      a = (a * a) % mod;
      b >>= 1;
   }
   return ans;
}

void prePower() {
   pw[0] = {1, 1};
   for(int i=1; i<N; i++) {
      pw[i].first = (1LL * pw[i-1].first * b1) % M1;
      pw[i].second = (1LL * pw[i-1].second * b2) % M2;
   }

   ll p1_inv = big_mod(b1, M1-2, M1);
   ll p2_inv = big_mod(b2, M2-2, M2);
   
   ipw[0] = {1, 1};
   for(int i=1; i<N; i++) {
      ipw[i].first = (1LL * ipw[i-1].first * p1_inv) % M1;
      ipw[i].second = (1LL * ipw[i-1].second * p2_inv) % M2;
   }
}

pair<int, int> hash_of(string s) {
    int n = s.size();
    pair<int, int> hs = {0, 0};
    for(int i=0; i<n; i++) {
        hs.first += (1LL * s[i] * pw[i].first) % M1;
        hs.first %= M1;
        hs.second += (1LL * s[i] * pw[i].second) % M2;
        hs.second %= M2;
    }
    return hs;
}

void build(string s) {
    int n = s.size();
    for(int i=0; i<n; i++) {
        pref[i].first = (1LL * s[i] * pw[i].first) % M1;
        if(i) pref[i].first = (pref[i].first + pref[i-1].first) % M1;
        pref[i].second = (1LL * s[i] * pw[i].second) % M2;
        if(i) pref[i].second = (pref[i].second + pref[i-1].second) % M2;
    }
}

pair<int, int> get_hash(int i, int j) {
    pair<int, int> hs = {0, 0};
    hs.first = pref[j].first;
    if(i) hs.first = ( ((hs.first - pref[i-1].first) % M1) + M1) % M1;
    hs.first = (1LL * hs.first * ipw[i].first) % M1;

    hs.second = pref[j].second;
    if(i) hs.second = ( ((hs.second - pref[i-1].second) % M2) + M2) % M2;
    hs.second = (1LL * hs.second * ipw[i].second) % M2;
    return hs;
}

int main() {
    prePower();
    string a, b; cin >> a >> b;
    ll n = a.size(), m = b.size();
    build(a);
    pair<int, int> hs_b = hash_of(b);
    
    ll score = 0;
    for(int i=0; i<n; ++i) {
        if(i+m-1 < n) {
            pair<int, int> hs_a = get_hash(i, i+m-1);
            score += (hs_b == hs_a);
        }
    }
    cout << score << endl;
}
