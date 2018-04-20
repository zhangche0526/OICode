#include<iostream>
#include<cstdio>

const int MAXN=205;

int n,m;
double f[MAXN][2],g[MAXN];

int main()
{
	int i,j;scanf("%d%d",&n,&m);
	for(g[1]=1,i=2;i<=n;i++) g[i]=g[i-1]/m;
	for(f[0][1]=1,i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
			f[j][0]+=(double)(j-i)*g[j-i]*(f[i][0]*(double)(m-2)/m+f[i][1]*(double)(m-1)/m),
			f[j][1]+=(double)(j-i)*g[j-i]*f[i][0]/m;
	double ans=g[n]*n;
	for(i=1;i<=n;i++) ans+=(double)i*(double)i*f[n-i][0]*g[i];
	printf("%.5lf",ans);
	return 0;
}
