//https://lightoj.com/problem/making-huge-palindromes
//String Hashing
//primes = {285897553, 745494041, 693888673, 950758511, 282174533, 847345579, 722520917, 354688703, 963459817, 139793893};
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

#define pb push_back
#define MOD 1000000007
#define vll vector<ll>
#define endl "\n" 
#define all(v) v.begin(), v.end()
#define mem(a,b) memset(a, b, sizeof(a))
#define co(n) cout << n << endl
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define fr(x, n) for (int i = x; i < n; ++i)
#define fraction(x) cout << fixed << setprecision(x)
#define Baba_Yaga ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL);
 
const double eps = 1e-9;

ll gcd(ll a,ll b) { return __gcd(a,b); }
ll lcm(ll a,ll b) { return (a*b)/__gcd(a,b); }

int dx[] = {0, 0, +1, -1, +1, +1, -1, -1};
int dy[] = {+1, -1, 0, 0, +1, -1, +1, -1};


const int N = 1e6+12;
const int p1 = 137, p2 = 277;
const int M1 = 1e9+7, M2 = 139793893;
pair<int, int> pw[N], ipw[N], pref[N], pref_2[N];


ll big_mod(ll a, ll b, ll mod)
{
    ll ans = 1;
    while(b)
    {
        if(b & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

void prePower()
{
    pw[0]={1, 1};
    for(int i=1; i<N; i++)
    {
        pw[i].first = (1LL * pw[i-1].first * p1) % M1;
        pw[i].second = (1LL * pw[i-1].second * p2) % M2;
    }

    int p1_inv = big_mod(p1, M1-2, M1);
    int p2_inv = big_mod(p2, M2-2, M2);
    ipw[0] = {1, 1};
    for(int i=1; i<N; i++)
    {
        ipw[i].first = (1LL * ipw[i-1].first * p1_inv) % M1;
        ipw[i].second = (1LL * ipw[i-1].second * p2_inv) % M2;
    }
}

pair<int, int> hash_of(string s)
{
    int n = s.size();
    pair<int, int> hs = {0, 0};
    for(int i=0; i<n; i++)
    {
        hs.first += (1LL * s[i] * pw[i].first) % M1;
        hs.first %= M1;

        hs.second += (1LL * s[i] * pw[i].second) % M2;
        hs.second %= M2;
    }
    return hs;
}

void build(string s)
{
    int n = s.size();
    for(int i=0; i<n; i++)
    {
        pref[i].first = (1LL * s[i] * pw[i].first) % M1;
        if(i) pref[i].first = (pref[i].first + pref[i-1].first) % M1;
        
        pref[i].second = (1LL * s[i] * pw[i].second) % M2;
        if(i) pref[i].second = (pref[i].second + pref[i-1].second) % M2;
    }
}
void build_2(string s)
{
    int n = s.size();
    for(int i=0; i<n; i++)
    {
        pref_2[i].first = (1LL * s[i] * pw[i].first) % M1;
        if(i) pref_2[i].first = (pref_2[i].first + pref_2[i-1].first) % M1;
        
        pref_2[i].second = (1LL * s[i] * pw[i].second) % M2;
        if(i) pref_2[i].second = (pref_2[i].second + pref_2[i-1].second) % M2;
    }
}

pair<int, int> get_hash(int i, int j)
{
    pair<int, int> hs = {0, 0};
    
    hs.first = pref[j].first;
    if(i) hs.first = (hs.first - pref[i-1].first + M1) % M1;
    hs.first = (1LL * hs.first * ipw[i].first) % M1;

    hs.second = pref[j].second;
    if(i) hs.second = (hs.second - pref[i-1].second + M2) % M2;
    hs.second = (1LL * hs.second * ipw[i].second) % M2;
    
    return hs;
}

pair<int, int> get_hash_2(int i, int j)
{
    pair<int, int> hs = {0, 0};
    
    hs.first = pref_2[j].first;
    if(i) hs.first = (hs.first - pref_2[i-1].first + M1) % M1;
    hs.first = (1LL * hs.first * ipw[i].first) % M1;

    hs.second = pref_2[j].second;
    if(i) hs.second = (hs.second - pref_2[i-1].second + M2) % M2;
    hs.second = (1LL * hs.second * ipw[i].second) % M2;
    
    return hs;
}


void solve()
{
    string s, t; cin >> s;
    t = s;
    reverse(all(t));
    build(s);
    build_2(t);
    int n = s.size();
    int maxi = 0;
    for(int i=n-1; i>=0; i--)
    {
        if(get_hash(i, n-1) == get_hash_2(0, n-i-1))
        {
            maxi = max(maxi, n-i);
        }
    }
    cout << s.size() + s.size() - maxi << endl;
}

int main()
{
    prePower();
    int t = 1; cin >> t;
    for(int i=1; i<=t; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}
