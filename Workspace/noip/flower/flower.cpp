#include<iostream>
#include<cstdio>
#include<cmath>

const int MAXN=505,MAXM=13e4+5;
const double eps=1e-6;

int n,m;
struct E{int next,to,val;} e[MAXM<<1];int ecnt,G[MAXN];int outDgr[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;outDgr[u]++;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}

double equ[MAXN][MAXN];
void guass()
{
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		int num=i;
		for(j=i+1;j<=n;j++)
			if(std::fabs(equ[num][i])<std::fabs(equ[j][i]))
				num=j;
		std::swap(equ[num],equ[i]);
		for(j=i+1;j<=n;j++)
		{
			double t=equ[j][i]/equ[i][i];
			for(k=i;k<=n+1;k++) equ[j][k]-=equ[i][k]*t;
		}
	}
	for(i=n;i;i--)
	{
		for(j=i+1;j<=n;j++)
			equ[i][n+1]-=equ[i][j]*equ[j][n+1];
		equ[i][n+1]/=equ[i][i];
	}
}

int main()
{
//	freopen("flower.in","r",stdin);
//	freopen("flower.out","w",stdout);
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);
	}
	for(int u=1;u<n;u++)
	{
		equ[u][u]=outDgr[u];
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			equ[u][v]=-1.0;
			equ[u][n+1]+=e[i].val;
		}
	}
	equ[n][n]=1.0;
	guass();
	printf("%.1lf",equ[1][n+1]+eps);
	return 0;
}

/*
6 8
1 2 3
1 3 2
2 4 1
2 3 2
3 5 4
4 5 3
4 6 2
5 6 3
*/
