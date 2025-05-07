//https://lightoj.com/problem/not-the-best
// undirected both front and back dijkstra :)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define vll vector<ll>
#define pll pair<ll, ll>
#define endl "\n" 
#define all(v) v.begin(), v.end()
#define fr(x, n) for (int i = x; i < n; ++i)
const int N = 5e3+12;

struct hella
{
    ll u, v, w;
};


vector<pll> g[N];
ll dist[2][N];

void dijkstra(ll src, ll n, ll which) {
    for(int i=0; i<=n; i++) dist[which][i] = LLONG_MAX;
    dist[which][src] = 0;

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, src});

    while(!pq.empty()) {
        ll u = pq.top().second, curD = pq.top().first;
        pq.pop();
        if(curD > dist[which][u]) continue;

        for(auto edge : g[u]) {
            ll v = edge.first, weight = edge.second;
            if(curD + weight < dist[which][v]) {
                dist[which][v] = curD + weight;
                pq.push({dist[which][v], v});
            }
        }
    }
}

void solve() {
    for(int i=0; i<=5e3; i++) g[i].clear();
    vector<hella> roads;

    ll n, m; cin >> n >> m;
    for(int i=0; i<m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        roads.push_back({u, v, w});
    }

    dijkstra(1, n, 0);
    dijkstra(n, n, 1);
    ll min_dist = dist[0][n];
    ll __2nd_best = LLONG_MAX;

    for(auto x : roads) {
        ll mini = min(dist[0][x.u] + dist[1][x.v], dist[1][x.u] + dist[0][x.v]);
        if(mini + x.w == min_dist) {
            __2nd_best = min(__2nd_best, mini + (3*x.w));
        }
        if(mini + x.w > min_dist) {
            __2nd_best = min(__2nd_best, mini + x.w);
        }
    }
    cout << __2nd_best << endl;
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
