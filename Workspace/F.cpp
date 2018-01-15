#include<iostream>
#include<cstdio>
inline int abs(int x){if(x<0) return -x;return x;}
const int MAXN=1e5+5;

int n,m;
int a[MAXN],R[MAXN];

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	int lp,rp=1;
	for(lp=1;lp<=n;lp++)
	{
		if(rp<lp) rp=lp;
		while(rp<n&&abs(a[rp]-a[rp+1])<=1)
			rp++;
		R[lp]=rp;
	}
	while(m--)
	{
		int l,r;scanf("%d%d",&l,&r);
		if(r<=R[l]) puts("YES");
		else        puts("NO");
	}
	return 0;
}
