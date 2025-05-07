//https://lightoj.com/problem/back-to-underworld
// biparted kinda problem
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

#define pb push_back
#define MOD 1000000007
#define vll vector<ll>
#define pll pair<ll, ll>
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
const int N = 2e4+123;

ll gcd(ll a,ll b) { return __gcd(a,b); }
ll lcm(ll a,ll b) { return (a*b)/__gcd(a,b); }

int dx[] = {0, 0, +1, -1, +1, +1, -1, -1};
int dy[] = {+1, -1, 0, 0, +1, -1, +1, -1};

vll arr[N];
bool vis[N];
vll have(N);

ll m;
ll ct = 0, ct1 = 0;

void dfs(ll k, ll color)
{
    vis[k] = 1;
    if(color == 1) ct1++;
    ct++;

    ll temp;
    if(color == 1) temp = 2;
    else temp = 1;

    for(auto u : arr[k])
    {
        if(!vis[u])
        {
            dfs(u, temp);
        }
    }
}


void solve()
{

    for(int i=0; i<N; i++)
    {
        vis[i] = false;
        arr[i].clear();
        have[i] = 0;
    }

    cin >> m;
    for(int i=0; i<m; i++)
    {
        ll u, v; cin >> u >> v;
        arr[u].push_back(v);
        arr[v].push_back(u);
        have[u] = 1, have[v] = 1;
    }
    ll ans = 0;

    for(int i=1; i<=N; i++)
    {
        if( (have[i] == 1) && (vis[i] == 0))
        {
            ct = 0, ct1 = 0;
            dfs(i, 1);
            ans += max(ct1, ct-ct1);
        }

    }
    cout << ans << endl;

}

// --- Think the problem backwards ---

int main()
{
    Baba_Yaga;
    ll tc = 1; cin >> tc;
    ll i = 0;
    while(tc--)
    {
        i++;
        cout << "Case " << i << ": ";
        solve();

    } 
}
