// https://cses.fi/problemset/task/1194
//bfs_from_multiple_source

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
const int N = 1005;

ll gcd(ll a,ll b) { return __gcd(a,b); }
ll lcm(ll a,ll b) { return (a*b)/__gcd(a,b); }

int dx[] = {0, 0, 1, -1, 1, -1, -1, 1};
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

ll n, m;
char arr[N][N];

ll lvl_monster[N][N];
bool vis_monster[N][N];
ll lvl_me[N][N];
bool vis_me[N][N];
map<pair<ll, ll>, pair<ll,ll>> parent;
vector<pair<ll, ll>> vp;

bool isPoss = false;
pair<ll, ll> p;
ll ans = LLONG_MAX;

void bfs_monster()
{
    queue<pair<ll, ll>> q;
    for(int i=0; i<vp.size(); i++)
    {
        ll ii = vp[i].first, jj = vp[i].second;
        q.push({ii, jj});
        lvl_monster[ii][jj] = 0;
        vis_monster[ii][jj] = true;
    }
    while(!q.empty())
    {
        ll i = q.front().first, j = q.front().second;
        q.pop();
        for(int k=0; k<4; k++)
        {
            ll ii = i + dx[k];
            ll jj = j + dy[k];
            if(ii >= 1 && jj >= 1 && ii <= n && jj <= m && arr[ii][jj] != '#' && arr[ii][jj] != 'M' && !vis_monster[ii][jj])
            {
                lvl_monster[ii][jj] = lvl_monster[i][j] + 1;
                vis_monster[ii][jj] = true;
                q.push({ii, jj});
            }
        }
    }

}

void bfs_me(ll x, ll y)
{
    vis_me[x][y] = true;
    lvl_me[x][y] = 0;
    queue<pair<ll, ll>> q;
    q.push({x, y});
    while(!q.empty())
    {
        ll i = q.front().first, j = q.front().second;
        q.pop();
        for(int k=0; k<4; k++)
        {
            ll ii = i + dx[k];
            ll jj = j + dy[k];
            if(ii >= 1 && jj >= 1 && ii <= n && jj <= m && arr[ii][jj] != '#' && arr[ii][jj] != 'M' && !vis_me[ii][jj])
            {
                lvl_me[ii][jj] = lvl_me[i][j] + 1;
                vis_me[ii][jj] = true;
                q.push({ii, jj});
                parent[{ii, jj}] = {i, j};

                if( (ii == 1 || ii == n || jj == 1 || jj == m ) && (lvl_monster[ii][jj] == -1 || lvl_monster[ii][jj] > lvl_me[ii][jj]))
                {
                    // ans = min(lvl_me[ii][jj], ans);
                    if(ans >= lvl_me[ii][jj])
                    {
                        ans = lvl_me[ii][jj];
                        p = make_pair(ii, jj);
                    }
                    isPoss = true;
                }
            }
        }
    }
}

void solve()
{
    mem(lvl_monster, -1);
    mem(lvl_me, -1);

    cin >> n >> m;
    ll x = 0, y = 0;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=m; j++)
        {
            cin >> arr[i][j];
            if(arr[i][j] == 'A')
            {
                x = i, y = j;
            }
            if(arr[i][j] == 'M')
            {
                vp.push_back({i, j});
            }
        }
    }
    if(x == 1 || x == n || y == 1 || y == m)
    {
        yes;
        cout << 0 << endl;
        return;
    }

    bfs_monster();
    bfs_me(x , y);

    if(!isPoss) 
    {
        no; return;
    }
    yes;
    cout << ans << endl;
    string s;
    while(parent.find(p) != parent.end())
    {
        ll i = p.first, j = p.second;
        ll p_i = parent[p].first, p_j = parent[p].second;
        if(j + 1 == p_j) s.push_back('L');
        else if(j - 1 == p_j) s.push_back('R');
        else if(i + 1 == p_i) s.push_back('U');
        else if(i - 1 == p_i) s.push_back('D');
        p = parent[p];
    }
    reverse(all(s));
    cout << s << endl;
}


// --- Think the problem backwards ---

int main()
{
    Baba_Yaga;
    ll tc = 1; // cin >> tc;
    while(tc--) solve();
}
