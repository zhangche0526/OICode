#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define rep(i, x, y) for (int i = (x), _ = (y); i < _; ++i)
#define down(i, x, y) for (int i = (x) - 1, _ = (y); i >= _; --i)
#define mp(x, y) {x, y}
#define pb(x) push_back(x)
#define bin(x) (1 << (x))
#define fi first
#define se second

template<typename T> inline bool upmax(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
template<typename T> inline bool upmin(T &x, const T &y) { return x > y ? x = y, 1 : 0; }

namespace MATH_CAL {
	const int mod = 1e9 + 7;
	constexpr int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
	constexpr int sub(int a, int b) { return a - b < 0 ? a - b + mod : a - b; }
	constexpr int mul(int a, int b) { return (ll) a * b % mod; }
	inline int qpow(int x, int n) { int r = 1; for ( ; n; n /= 2, x = mul(x, x)) if (n & 1) r = mul(r, x); return r; }
	inline int mod_inv(int x) { return qpow(x, mod - 2); }
}

const ll inf = 1ll << 60;
const int MAX_N = 3e5 + 10;

typedef pair<ll, int> data;

vector<pii> adj[MAX_N];
vector<pii> g[MAX_N];
data f[MAX_N][3];
int N, K;

data add(data a, data b, ll c = 0, int d = 0) {
	return mp(a.fi + b.fi + c, a.se + b.se + d);
}

int seq[MAX_N], dfs_clock;
int  D, MAX_D;

void dfs(int x, int fa) {
	seq[dfs_clock++] = x;
	D++;
	upmax(MAX_D, D);
	for (auto v : adj[x]) {
		int y = v.fi;
		if (y == fa) continue ;
		g[x].pb(v);
		dfs(y, x);
	}
	D--;
}

void work(ll V, data &res) {
 	down (i, N, 0) {
		int x = seq[i];
		f[x][0] = mp(-V, 1);
		f[x][1] = mp(-inf, 0);
		f[x][2] = mp(0, 0);
		for (auto v : g[x]) {
			int y = v.fi;
			ll l = V + v.se;
			static data r[3];
			copy(f[x], f[x] + 3, r);
			down (a, 3, 0) down (b, 3, 0) {
				upmax(f[x][a], add(r[a], f[y][b]));
				if (a < 2 and b < 2) {
					upmax(f[x][a + 1], add(r[a], f[y][b], l, -1));
				}
			}
		}
	}
	res = mp(-inf, -inf);
	rep (i, 0, 3) upmax(res, f[1][i]);
}

int main() {
//	freopen("lct.in","r",stdin);
//	freopen("lct.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N >> K; K++;
	ll L = 0, R = 0;
	rep (i, 1, N) {
		int x, y, w;
		cin >> x >> y >> w;
		adj[x].pb(mp(y, w));
		adj[y].pb(mp(x, w));
		R += max(w, 0);
		upmin(L, ll(-w));
	}
	for(int i=1;i<=N;i++) reverse(adj[i].begin(),adj[i].end());
	dfs(1, 0);
	data res;
	while (L <= R) {
		ll m = L + (R - L) / 2;
		work(m, res);
		res.se < K ? R = m - 1 : L = m + 1;
	}
	work(R, res);
	cout << res.fi + ll(K) * R << endl;
	return 0;
}
