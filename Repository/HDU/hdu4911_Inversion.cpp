#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 100000;
ll n, cnt, a[MAXN + 1], b[MAXN + 1];//b:树状数组,ls:离散后数组
ll k;
struct mark
{
	ll n, ln;//数值，原先编号;	
} ls[MAXN + 1];

ll lowbit(ll x){return x & (- x);}

void add(ll x, ll y)//x处加上y
{
	for(; x <= n; x += lowbit(x)) 
	{
		b[x] += y;
	}
}

ll sum(ll x)
{
	ll ans = 0;
	for(; x; x -= lowbit(x)) ans += b[x];
	return ans;
}

int cmp(const mark & a, const mark & b){return a.n < b.n;}

int main()
{
	int i, j;
	ios::sync_with_stdio(false);
	while(cin >> n >> k)
	{
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(ls, 0, sizeof(ls));
		for(i = 1; i <= n; i ++) cin >> a[i], ls[i].n = a[i], ls[i].ln = i;

		sort(ls + 1, ls + n + 1, cmp);
		
		cnt = 1;
		a[ls[1].ln] = cnt;
		for(i = 2; i <= n; i ++)
		{
			if((ls[i - 1].n != ls[i].n)) cnt ++;
			a[ls[i].ln] = cnt;
		}
		ll ans = 0;
		for(i = n; i >= 1; i--)
		{
			ans += sum(a[i] - 1);
			add(a[i], 1);
		}
		if(ans - k < 0) cout << 0 << endl; 
		else cout << ans - k << endl;
	}
	return 0;
}
