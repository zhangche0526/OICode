#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
const int MAXN=1e6+5;

int n;ll ans;

struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}

int sz[MAXN];
bool vis[MAXN];
void dfs(int u)
{
	vis[u]=true,sz[u]=1;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		dfs(v);
		ans+=(ll)e[i].val*abs(n-2*sz[v]);
		sz[u]+=sz[v];
	}
}

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);
	}
	dfs(1);
	printf("%lld",ans);
	return 0;
}
