#include<bits/stdc++.h>
using namespace std;
int n,m,k,v[20],a[200010],L[200010][20],R[200010][20],f[300000],g[300000],w[200010];
int main()
{
	int i,j,x;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	v[0]=m;
	while(v[k])
		v[++k]=v[k-1]/2;
	for(i=0;i<=k;i++)
	{
		for(j=x=1;j<=n;j++)
		{
			if(j>1 && a[j]-a[j-1]>v[i])
				x=j;
			L[j][i]=x;
		}
		for(j=x=n;j>0;j--)
		{
			if(j<n && a[j+1]-a[j]>v[i])
				x=j;
			R[j][i]=x;
		}
		R[n+1][i]=n+1;
	}
	for(i=0;i<(1<<k);i++)
		g[i]=n+1;
	for(i=1;i<(1<<k);i++)
		for(j=1;j<=k;j++)
			if(i&(1<<j-1))
			{
				f[i]=max(f[i],R[f[i^(1<<j-1)]+1][j]);
				g[i]=min(g[i],L[g[i^(1<<j-1)]-1][j]);
			}
	for(i=0;i<(1<<k);i++)
	{
		j=L[g[i]-1][0];
		x=R[f[(1<<k)-1^i]+1][0];
		if(j<=x)
			w[j]++,w[x+1]--;
	}
	for(i=1,x=0;i<=n;i++)
	{
		x+=w[i];
		if(x)
			printf("Possible\n");
		else
			printf("Impossible\n");
	}
	return 0;
}
