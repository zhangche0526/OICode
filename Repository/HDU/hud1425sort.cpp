#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 1000000;
typedef long long ll;
ll a[MAXN + 1];
ll n, m;
int main()
{
	ios::sync_with_stdio(false);
	ll i, j;
	while(cin >> n >> m)
	{
		for(i = 1; i <= n; i ++) cin >> a[i];
		sort(a + 1, a + n + 1);
		for(i = n; i > 1 && m > 1; i --, m --)
			cout << a[i] << " ";
		cout << a[i] << endl;
	}
	return 0;
}
