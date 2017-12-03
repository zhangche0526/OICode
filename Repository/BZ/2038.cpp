#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
typedef long long ll;

const int MAXN=5e4+5;

int n,m,pos[MAXN],c[MAXN];

ll s[MAXN],ans;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

struct D{int l,r,id;ll a,b;} a[MAXN];
bool cmp1(const D &a,const D &b)
{return pos[a.l]==pos[b.l]?a.r<b.r:a.l<b.l;}
bool cmp2(const D &a,const D &b)
{return a.id<b.id;}

void upd(int p,int det)
{
	ans-=s[c[p]]*s[c[p]];
	s[c[p]]+=det;
	ans+=s[c[p]]*s[c[p]];
}

void solve()
{
	for(int i=1,l=1,r=0;i<=m;i++)
	{
		for(;r<a[i].r;r++) upd(r+1,1);
		for(;r>a[i].r;r--) upd(r,-1);
		for(;l<a[i].l;l++) upd(l,-1);
		for(;l>a[i].l;l--) upd(l-1,1);
		if(a[i].l==a[i].r)
		{
			a[i].a=0;a[i].b=1;
			continue;
		}
		a[i].a=ans-(a[i].r-a[i].l+1);
		a[i].b=(ll)(a[i].r-a[i].l+1)*(a[i].r-a[i].l);
		ll t=gcd(a[i].a,a[i].b);
		a[i].a/=t,a[i].b/=t;
	}
}

int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&c[i]);
	int blkL=std::sqrt(n);
	for(i=1;i<=n;i++)
		pos[i]=(i-1)/blkL+1;
	for(i=1;i<=m;i++)
		scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i;
	std::sort(a+1,a+m+1,cmp1);
	solve();
	std::sort(a+1,a+m+1,cmp2);
	for(i=1;i<=m;i++) printf("%lld/%lld\n",a[i].a,a[i].b);
}
