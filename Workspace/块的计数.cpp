#include<iostream>
#include<cstdio>

const int MAXN=1e6+5;

int N;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int sz[MAXN];
void dfs(int u,int la)
{
	sz[u]=1;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dfs(v,u);
		sz[u]+=sz[v];
	}
}

int main()
{
	int i,j;scanf("%d",&N);
	for(i=1;i<N;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	static int cnt[MAXN];
	dfs(1,0);
	for(i=1;i<=N;i++) cnt[sz[i]]++;
	int ans=0;
	for(i=1;i<=N;i++)
	{
		for(j=i+i;j<=N;j+=i)
			cnt[i]+=cnt[j];
		if(i*cnt[i]==N) ans++;
	}
	printf("%d",ans);
	return 0;
}
