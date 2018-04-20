#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
template<typename Ty>
inline void umx(Ty &a,Ty b){a=max(a,b);}
typedef long long ll;
const int MAXN=2005;
const ll INF=1e18;

int n,K;

struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}

int sz[MAXN];
ll f[MAXN][MAXN];

void dfs(int u,int la)
{
	sz[u]=1;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dfs(v,u);
		static ll tmp[MAXN];std::fill(tmp,tmp+min(K,sz[u]+sz[v])+1,-INF);
		for(int a=0;a<=sz[u];a++)
			for(int b=0;b<=sz[v];b++)
				if(a+b<=K) umx(tmp[a+b],f[u][a]+f[v][b]+((ll)b*(K-b)+(ll)(sz[v]-b)*(n-K-(sz[v]-b)))*e[i].val);
		sz[u]+=sz[v];
		std::copy(tmp,tmp+min(K,sz[u])+1,f[u]);
	}
}

int main()
{
	int i;scanf("%d%d",&n,&K);
	for(i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);
	}
	dfs(1,0);
	printf("%lld",f[1][K]);
	return 0;
}
