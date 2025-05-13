// https://lightoj.com/problem/country-roads (in of all max) roads cost
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vll vector<ll>
#define pll pair<ll, ll>
#define endl "\n" 
#define all(v) v.begin(), v.end()
#define fr(x, n) for (int i = x; i < n; ++i)
const int N = 505;

vector<pll> g[N];
ll dist[N];

void dijkstra(ll src, ll n)
{
    for(int i=0; i<=n; i++) dist[i] = 1e18;
    dist[src] = 0;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, src});
    
    while(!pq.empty())
    {
        ll curDist = pq.top().first, u = pq.top().second;
        pq.pop();
        
        if(curDist > dist[u]) continue;

        for(auto [v, w] : g[u])
        {  
            ll maxi = max(curDist, w);

            if(maxi < dist[v])
            {
                dist[v] = maxi;
                pq.push({dist[v], v});
            }
        }
    }
}


void solve() {
    ll n, m; cin >> n >> m;
    for(int i=0; i<=n; i++) g[i].clear();

    for(int i=0; i<m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    ll src; cin >> src;
    dijkstra(src, n);

    for(int i=0; i<n; i++) {
        if(dist[i] == 1e18) cout << "Impossible" << endl;
        else cout << dist[i] << endl;
    }
}

// --- Try to formulate equations. ---

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); 
    cout.tie(0);

    ll tc = 1, i = 1; cin >> tc;
    while(tc--) {
        cout << "Case " << i++ << ": " << endl;
        solve();
    }
}
