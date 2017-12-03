#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

const int MAXN=55;
const double INF=1e9,eps=1e-4;

int n;
double x[MAXN],y[MAXN];
double f[MAXN][MAXN];

double calS(int i,int j,int k)
{return std::fabs((x[j]-x[i])*(y[k]-y[i])-(x[k]-x[i])*(y[j]-y[i]))/2.0;}

bool jud(int i,int j,int k)
{
	for(int t=1;t<=n;t++) if(t!=i&&t!=j&&t!=k)
		if(std::fabs(calS(i,j,k)-calS(i,j,t)-calS(i,k,t)-calS(j,k,t))<eps)
			return false;
	return true;
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i,j,k;
		scanf("%d",&n);
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++) scanf("%lf%lf",x+i,y+i);
		for(i=n;i;i--)
			for(j=i+2;j<=n;j++)
			{
				f[i][j]=INF;
				for(k=i+1;k<j;k++) if(jud(i,j,k))
					f[i][j]=std::min(f[i][j],std::max(calS(i,j,k),std::max(f[i][k],f[k][j])));
			}
		printf("%.1f\n",f[1][n]);
	}
	return 0;
}
