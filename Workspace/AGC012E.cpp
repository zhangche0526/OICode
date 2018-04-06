#include<iostream>
#include<cstdio>
#include<algorithm>
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
const int MAXN=2e5+5,MAXS=3e5+5;

int n,V,K,v[MAXN];int na[MAXN];
int L[MAXN][20],R[MAXN][20];
int f[MAXS],g[MAXS];
int seq[MAXN];

int main()
{
	int i,k,x;scanf("%d%d",&n,&V);
	for(i=1;i<=n;i++) scanf("%d",na+i);

	v[0]=V;while(v[K]) v[++K]=v[K-1]>>1;

	for(k=0;k<=K;k++)
	{
		for(i=x=1;i<=n;i++)
			L[i][k]=x=(i>1&&na[i]-na[i-1]>v[k])?i:x;
		for(i=x=n;i;i--)
			R[i][k]=x=(i<n&&na[i+1]-na[i]>v[k])?i:x;
		R[n+1][k]=n+1;
	}

	std::fill(g,g+(1<<K),n+1);
	for(int S=1;S<1<<K;S++)
		for(k=1;k<=K;k++)
			if((S>>k-1)&1)
				umx(f[S],R[f[S^(1<<k-1)]+1][k]),
				umn(g[S],L[g[S^(1<<k-1)]-1][k]);

	for(int S=0,msk=(1<<K)-1;S<1<<K;S++)
	{
		int l=L[g[S]-1][0],r=R[f[msk^S]+1][0];
		if(l<=r) seq[l]++,seq[r+1]--;
	}

	for(i=1;i<=n;i++) seq[i]+=seq[i-1];
	for(i=1;i<=n;i++) puts(seq[i]?"Possible":"Impossible");
	return 0;
}
