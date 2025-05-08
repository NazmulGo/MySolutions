// https://lightoj.com/problem/new-traffic-system
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vll vector<ll>
#define pll pair<ll, ll>
#define endl "\n" 
#define all(v) v.begin(), v.end()
#define fr(x, n) for (int i = x; i < n; ++i)
const int N = 1e4+12;
const ll mx = 1e17;

vector<vll> g[N];
ll dist[11][N];

void dijkstra(ll src, ll n, ll d) {
    for(int i=0; i<11; i++) {
        for(int j=0; j<N; j++) dist[i][j] = mx;
    }
    dist[0][src] = 0;

    priority_queue< vll, vector<vll>, greater<vll> >pq;
    pq.push({0, 0, src});

    while(!pq.empty()) {
        ll curD = pq.top()[0], ct = pq.top()[1], u = pq.top()[2];
        pq.pop();
        if(curD > dist[ct][u]) continue;

        for(auto edge : g[u]) {
           ll v = edge[0], weight = edge[1], typ = edge[2];
           if(typ + ct <= d && dist[typ + ct][v] > dist[ct][u] + weight) {
                dist[typ + ct][v] = dist[ct][u] + weight;
                pq.push({dist[typ + ct][v], typ+ct, v});
           }            
        }
    }

}

void solve() {
    ll n, m, k, d; cin >> n >> m >> k >> d;
    for(int i=0; i<=n; i++) g[i].clear();
    for(int i=0; i<m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w, 0});
    }
    for(int i=0; i<k; i++) {
        ll u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w, 1});
    }

    dijkstra(0, n, d);
    ll mini = mx;
    for(int i=0; i<=d; i++)  {
        mini = min(mini, dist[i][n-1]);
    }
    if(mini == mx) cout << "Impossible" << endl;
    else cout << mini << endl; 
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
