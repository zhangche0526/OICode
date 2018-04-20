#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using std::fabs;

const int MAXN=505,MAXM=25e4+5;

int n,m;

int d[MAXN];
struct E{int next,to;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}
struct A{int u,v;} a[MAXM];int acnt;

double equ[MAXN][MAXN];
void gauss(int n,double *ans)
{
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		int mxp=i;
		for(j=i+1;j<=n;j++)
			if(fabs(equ[j][i])>fabs(equ[mxp][i]))
				mxp=j;
		if(mxp!=i) std::swap(equ[i],equ[mxp]);
		for(j=i+1;j<=n;j++)
		{
			double t=equ[j][i]/equ[i][i];
			for(k=i+1;k<=n+1;k++)
				equ[j][k]-=equ[i][k]*t;
		}
	}
	for(i=n;i;i--)
	{
		for(j=i+1;j<=n;j++)
			equ[i][n+1]-=equ[i][j]*equ[j][n+1];
		equ[i][n+1]/=equ[i][i];
	}
	for(i=1;i<=n;i++) ans[i]=equ[i][n+1];
}

double f[MAXM],g[MAXN];

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);a[++acnt]=(A){u,v};
		addEdge2(u,v);d[u]++,d[v]++;
	}
	equ[1][n]=-1.0;
	for(int u=1;u<n;u++)
	{
		equ[u][u]=-1.0;
		for(int v=e[i=G[u]].to;i;v=e[i=e[i].next].to)
			if(v!=n) equ[u][v]=1.0/d[v];
	}
	gauss(n-1,g);
	for(i=1;i<=m;i++) f[i]=g[a[i].u]/d[a[i].u]+g[a[i].v]/d[a[i].v];
	std::sort(f+1,f+m+1,std::greater<double>());
	double ans=0;
	for(i=1;i<=m;i++) ans+=f[i]*i;
	printf("%.3lf",ans);
	return 0;
}
/*
3 3
2 3
1 2
1 3
*/
