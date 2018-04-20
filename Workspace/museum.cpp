#include<iostream>
#include<cstdio>
#include<cmath>
using std::fabs;

const int MAXN=25,MAXM=405;

int n,m,A,B;

int d[MAXN],id[MAXN][MAXN];
struct E{int next,to;} e[MAXM];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

double equ[MAXM][MAXM];

void guass(int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		int mxp=i;
		for(j=i+1;j<n;j++)
			if(fabs(equ[j][i])>fabs(equ[mxp][i]))
				mxp=j;
		if(mxp!=i) std::swap(equ[i],equ[mxp]);
		for(j=i+1;j<n;j++)
		{
			double t=equ[j][i]/equ[i][i];
			for(k=i;k<=n;k++) equ[j][k]-=equ[i][k]*t;
		}
	}
	for(i=n-1;~i;i--)
	{
		for(j=i+1;j<n;j++)
			equ[i][n]-=equ[i][j]*equ[j][n];
		equ[i][n]/=equ[i][i];
	}
}

double p[MAXN],q[MAXN];

int main()
{
	int i,j;scanf("%d%d%d%d",&n,&m,&A,&B);
	for(i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);d[u]++,d[v]++;
	}
	for(i=1;i<=n;i++) scanf("%lf",p+i);
	for(i=1;i<=n;i++) q[i]=(1.0-p[i])/d[i];
	int idcnt=0;for(i=1;i<=n;i++) for(j=1;j<=n;j++) id[i][j]=idcnt++;
	for(int u1=1;u1<=n;u1++) for(int u2=1;u2<=n;u2++)
	{
		equ[id[u1][u2]][id[u1][u2]]=1.0-(u1!=u2?p[u1]*p[u2]:0);
		for(int v1=e[i=G[u1]].to;i;v1=e[i=e[i].next].to) if(v1!=u2)
			equ[id[u1][u2]][id[v1][u2]]=-q[v1]*p[u2];
		for(int v2=e[i=G[u2]].to;i;v2=e[i=e[i].next].to) if(u1!=v2)
			equ[id[u1][u2]][id[u1][v2]]=-p[u1]*q[v2];
		for(int v1=e[i=G[u1]].to;i;v1=e[i=e[i].next].to)
			for(int v2=e[j=G[u2]].to;j;v2=e[j=e[j].next].to)	if(v1!=v2)
			equ[id[u1][u2]][id[v1][v2]]=-q[v1]*q[v2];
	}
	equ[id[A][B]][n*n]=1.0;
	guass(n*n);
	for(i=1;i<=n;i++) printf("%.6lf ",equ[id[i][i]][n*n]);
	return 0;
}

