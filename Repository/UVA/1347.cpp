#include<iostream>
#include<cstdio>
#include<cmath>

const int MAXN=55;

int n;

double x[MAXN],y[MAXN];
double dis[MAXN][MAXN],f[MAXN][MAXN];

int main()
{
	while(~scanf("%d",&n))
	{
		int i,j;
		for(i=1;i<=n;i++)
			scanf("%lf%lf",x+i,y+i);
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				dis[i][j]=std::sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		for(j=1;j<n-1;j++) f[n-1][j]=dis[n-1][n]+dis[j][n];
		for(i=n-2;i>=2;i--)
			for(j=1;j<i;j++)
				f[i][j]=std::min(dis[i][i+1]+f[i+1][j],dis[j][i+1]+f[i+1][i]);
		printf("%.2f\n", dis[1][2]+f[2][1]);
	}
	return 0;
}
