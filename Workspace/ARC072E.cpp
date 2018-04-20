#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
const int MAXN=5e5+5;

int n,D,Q;
int d[MAXN],q[MAXN];

int f[MAXN],g[MAXN];

int main()
{
	int i;scanf("%d%d",&n,&D);
	for(i=1;i<=n;i++) scanf("%d",d+i);
	scanf("%d",&Q);
	for(i=1;i<=Q;i++) scanf("%d",q+i);

	f[1]=D;for(i=2;i<=n;i++) f[i]=min(f[i-1],abs(f[i-1]-d[i-1]));
	g[n]=1;for(i=n-1;i;i--) g[i]=g[i+1]+(d[i+1]<2*g[i+1]?d[i+1]:0);
	for(i=1;i<=Q;i++) puts(f[q[i]]>=g[q[i]]?"YES":"NO");
	return 0;
}
