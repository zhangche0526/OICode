#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>

const int MAXN=20;

int n,m;
double X[MAXN],Y[MAXN];
int f[1<<20],g[MAXN][MAXN];

bool equ(double x,double y){return std::fabs(x-y)<1e-6;}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i,j,t; 
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++) scanf("%lf%lf",X+i,Y+i);
		memset(g,0,sizeof(g));
		for(i=1;i<=n;i++)
			for(j=i+1;j<=n;j++)
			{
				if(equ(X[i],X[j])) continue;
				double a=(Y[j]/X[j]-Y[i]/X[i])/(X[j]-X[i]);
				if(a>=0) continue;
				double b=Y[i]/X[i]-a*X[i];
				for(t=1;t<=n;t++) if(equ(a*X[t]+b,Y[t]/X[t]))
					g[i][j]|=(1<<t-1);
			}
		memset(f,127,sizeof(f));f[0]=0;
		for(i=0;i<(1<<n);i++)
			for(j=1;j<=n;j++)
			{
				if(i&(1<<j-1)) continue;
				for(t=j+1;t<=n;t++) f[i|g[j][t]]=std::min(f[i|g[j][t]],f[i]+1);
				f[i|(1<<j-1)]=std::min(f[i|(1<<j-1)],f[i]+1);
			}
		printf("%d\n",f[(1<<n)-1]);
	}
	return 0;
}
