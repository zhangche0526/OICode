#include<iostream>
#include<cstdio>
#include<cmath>

const int MAXN=5e5+5;
const double eps=1e-9;

inline double readp()
{int res;scanf("%d",&res);return res*0.01;}

int n;

struct E{int next,to;double p;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,double p){e[++ecnt]=(E){G[u],v,p};G[u]=ecnt;}
void addEdge2(int u,int v,double p){addEdge(u,v,p);addEdge(v,u,p);}
double q[MAXN];

double f[MAXN],g[MAXN];

void dfs1(int u,int la)
{
	g[u]=q[u];
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dfs1(v,u);
		g[u]=g[u]+g[v]*e[i].p-g[u]*g[v]*e[i].p;
	}
}

void dfs2(int u,int la)
{
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		if(fabs(1.0-g[v]*e[i].p)<eps) f[v]=1.0;
		else
		{
			double t=(f[u]-g[v]*e[i].p)/(1.0-g[v]*e[i].p);
			f[v]=g[v]+t*e[i].p-g[v]*t*e[i].p;
		}
		dfs2(v,u);
	}
}

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v,readp());
	}
	for(i=1;i<=n;i++) q[i]=readp();
	dfs1(1,0);
	f[1]=g[1];
	dfs2(1,0);
	double ans=0;
	for(i=1;i<=n;i++) ans+=f[i];
	printf("%.6lf",ans);
	return 0;
}
