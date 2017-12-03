#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=2e3+5,MAXM=2e3+5,MAXV=305,MAXE=9e4+5,INF=1e9;

int N,M,V,E;
int C[MAXN],D[MAXN];double K[MAXN];

int dis[MAXV][MAXV];
inline void floyd()
{
	int i,j,k;
	for(k=1;k<=V;k++)
		for(i=1;i<=V;i++)
			for(j=1;j<=V;j++)
				if(dis[i][k]+dis[k][j]<dis[i][j])
					dis[i][j]=dis[i][k]+dis[k][j];
}

double f[MAXN][MAXM][2];
inline void calc()
{
	int i,j;
	for(i=2;i<=N;i++)
		for(j=0;j<=std::min(i,M);j++)
		{
			f[i][j][0]=std::min(f[i-1][j][0]+dis[C[i-1]][C[i]],
								f[i-1][j][1]+dis[D[i-1]][C[i]]*K[i-1]+dis[C[i-1]][C[i]]*(1.0-K[i-1]));
			if(j) f[i][j][1]=std::min(f[i-1][j-1][0]+dis[C[i-1]][D[i]]*K[i]+dis[C[i-1]][C[i]]*(1.0-K[i]), 
									  f[i-1][j-1][1]+dis[D[i-1]][D[i]]*K[i-1]*K[i]+dis[D[i-1]][C[i]]*K[i-1]*(1.0-K[i])+
									                 dis[C[i-1]][D[i]]*(1.0-K[i-1])*K[i]+dis[C[i-1]][C[i]]*(1.0-K[i-1])*(1.0-K[i]));
		}
}

int main()
{
	int i,j;
	scanf("%d%d%d%d",&N,&M,&V,&E);	
	for(i=1;i<=N;i++) scanf("%d",C+i);
	for(i=1;i<=N;i++) scanf("%d",D+i);
	for(i=1;i<=N;i++) scanf("%lf",K+i);
	for(i=1;i<=V;i++) for(j=1;j<=V;j++)
			if(i!=j) dis[i][j]=INF;
	for(i=1;i<=E;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		if(w<dis[u][v]) dis[u][v]=dis[v][u]=w;
	}
	floyd();
	for(i=1;i<=N;i++) for(j=0;j<=M;j++)
		f[i][j][0]=f[i][j][1]=INF;
	f[1][0][0]=f[1][1][1]=0;
	calc();
	double ans=INF;
	for(i=0;i<=M;i++) ans=std::min(ans,std::min(f[N][i][0],f[N][i][1]));
	printf("%.2f\n",ans);
	return 0;
}
