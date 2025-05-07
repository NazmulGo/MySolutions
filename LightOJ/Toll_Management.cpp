//https://lightoj.com/problem/toll-management
//directed, reverse graph before 2nd dijkstra

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vll vector<ll>
#define pll pair<ll, ll>
#define endl "\n" 
#define all(v) v.begin(), v.end()
#define fr(x, n) for (int i = x; i < n; ++i)
const int N = 1e4+12;
const ll mx = 1e18;

struct Toll
{
    ll u, v, w;
};

vector<pll> g[2][N];
ll dist[2][N];

void dijkstra(ll src, ll n, ll typ) {
    for(int i=0; i<=n; i++) dist[typ][i] =  mx;
    dist[typ][src] = 0;
    
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, src});
    
    while(!pq.empty()) {
        ll u = pq.top().second, curD = pq.top().first;
        pq.pop();
        if(dist[typ][u] < curD) continue;

        for(auto edge : g[typ][u]) {
            ll v = edge.first, weight = edge.second;

            if(curD + weight < dist[typ][v]) {
                dist[typ][v] = curD + weight;
                pq.push({dist[typ][v], v});
            }
        }
    }
}
void solve() {
    ll n, m, st, ed, k; cin >> n >> m >> st >> ed >> k;
    for(int i=0; i<=n; i++) g[0][i].clear(), g[1][i].clear();
    
    vector<Toll> roads;
    for(int i=0; i<m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        g[0][u].push_back({v, w});
        g[1][v].push_back({u, w});
        roads.push_back({u, v, w});
    }

    dijkstra(st, n, 0);
    dijkstra(ed, n, 1);

    ll maxi = -1;
    for(auto x : roads) {
        ll u = x.u, v = x.v, w = x.w;
        ll cost = dist[0][u] + w + dist[1][v];
        if(cost <= k) maxi = max(maxi, w);
    }
    cout << maxi << endl;
}

// --- Try to formulate equations. ---

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    cout.tie(0);

    ll tc = 1, i = 1; cin >> tc;
    while(tc--) {
        cout << "Case " << i++ << ": ";
        solve();

    }
}
