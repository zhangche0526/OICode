#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
inline void read(ll &x){
	x=0;char ch;bool flag = false;
	while(ch=getchar(),ch<'!');if(ch == '-') ch=getchar(),flag = true;
	while(x=10*x+ch-'0',ch=getchar(),ch>'!');if(flag) x=-x;
}
const ll maxn = 210010;
ll loger[maxn],minn[maxn][26],a[maxn];
ll minid[maxn][26];
inline void pre(ll n){
	loger[1] = 0;
	for(ll i=2;i<=n;++i){
		loger[i] = loger[i-1];
		if( i == (1 << loger[i]+1)) ++ loger[i];
	}
	for(ll i=n;i>=1;--i){
		minn[i][0] = a[i];
		minid[i][0] = i;
		for(ll j=1;i + (1<<j) - 1 <= n;++j){
			minn[i][j] = min(minn[i][j-1],minn[i+(1<<j-1)][j-1]);
			if(minn[i][j] == minn[i][j-1]) minid[i][j] = minid[i][j-1];
			if(minn[i][j] == minn[i+(1<<j-1)][j-1]) minid[i][j] = minid[i+(1<<j-1)][j-1];
		}
	}
}
inline ll query(ll l,ll r){
	ll k = loger[r-l+1];
	if(minn[l][k] < minn[r-(1<<k)+1][k]) return minid[l][k];
	return minid[r-(1<<k)+1][k];
}
ll belong[maxn];
struct Node{
	ll l,r,id;
	bool friend operator < (const Node &a,const Node &b){
		if(belong[a.l] == belong[b.l]) return a.r < b.r;
		return belong[a.l] < belong[b.l];
	}
}q[maxn];
ll anss[maxn],fl[maxn],fr[maxn];
ll sta[maxn],top;
inline void dp(ll n,ll *f){
	sta[top = 1] = 0;
	for(ll i=1;i<=n;++i){
		while(a[sta[top]] > a[i]) -- top;
		f[i] = (i - sta[top])*a[i] + f[sta[top]];
		sta[++top] = i;
	}
}
inline ll upd_R(ll l,ll r){
	ll p = query(l,r+1);
	return (p-l+1)*a[p] + fl[r+1] - fl[p];
}
inline ll upd_L(ll l,ll r){
	ll p = query(l-1,r);
	return (r-p+1)*a[p] + fr[l-1] - fr[p];
}
int main(){
#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
#endif
	ll n,Q;read(n);read(Q);a[0] = -(1LL<<60);
	for(ll i=1;i<=n;++i) read(a[i]);
	pre(n);dp(n,fl);reverse(a+1,a+n+1);//puts("reversed.");
	dp(n,fr);reverse(a+1,a+n+1);reverse(fr+1,fr+n+1);
	ll block = sqrt(n);
	for(ll i=1;i<=n;++i) belong[i] = (i/block) + 1;
	for(ll i=1;i<=Q;++i){
		read(q[i].l);read(q[i].r);
		q[i].id = i;
	}sort(q+1,q+Q+1);
	a[0] = 0;
	ll L = 1,R = 0,ans = 0;
	for(ll i=1;i<=Q;++i){
		while(R < q[i].r) ans += upd_R(L,R++);
		while(R > q[i].r) ans -= upd_R(L,--R);
		while(L > q[i].l) ans += upd_L(L--,R);
		while(L < q[i].l) ans -= upd_L(++L,R);
		anss[q[i].id] = ans;
	}
	for(ll i=1;i<=Q;++i){
		printf("%lld\n",anss[i]);
	}
	getchar();getchar();
	return 0;
}
