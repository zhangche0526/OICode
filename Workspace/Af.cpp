#include<iostream>
#include<cstdio>

const int MAXN=1005;

int n;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int a[MAXN];

int dis[MAXN];
void dfs(int u,int la)
{
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dis[v]=dis[u]+1;
		dfs(v,u);
	}
}

int main()
{
	freopen("A.in","r",stdin);
	freopen("Af.out","w",stdout);
	int i,j;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	for(i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	for(i=1;i<=n;i++)
	{
		dis[i]=0;dfs(i,0);
		int ans=0;
		for(j=1;j<=n;j++) if(dis[j]<=dis[1]) ans+=a[j];
		printf("%d\n",ans);
	}
	return 0;
}
