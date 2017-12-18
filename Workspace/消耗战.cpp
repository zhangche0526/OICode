#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::swap;
typedef long long ll;
const int MAXN=25e4+5;const ll INF=1e18;

int N,M,K;

const int rt=1;
struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w=0){if(u==v||!u||!v) return;e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w=0){addEdge(u,v,w);addEdge(v,u,w);}

ll mnv[MAXN],f[MAXN];
int dfn[MAXN],dcnt;int dpt[MAXN];
bool cmp(int a,int b){return dfn[a]<dfn[b];}

int anc[MAXN][20];
void dfs(int u)
{
	int i;dfn[u]=++dcnt;
	for(i=1;(1<<i)<=dpt[u];i++)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==anc[u][0]) continue;
		mnv[v]=min(mnv[u],(ll)e[i].val);
		dpt[v]=dpt[u]+1;
		anc[v][0]=u;
		dfs(v);
	}
}

int calLCA(int x,int y)
{   
	int i;if(dpt[x]<dpt[y]) std::swap(x,y);
	for(i=19;i>=0;i--)
		if(dpt[x]-(1<<i)>=dpt[y])
			x=anc[x][i];
	if(x==y) return x;
	for(i=19;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

int seq[MAXN],scnt;
int st[MAXN],tp;
void buildGraph()
{
	int i;ecnt=0;
	std::sort(seq+1,seq+1+K,cmp);
	scnt=1;
	for(i=2;i<=K;i++) if(calLCA(seq[scnt],seq[i])!=seq[scnt])
		seq[++scnt]=seq[i];
	st[tp=1]=1;
	for(i=1;i<=scnt;i++)
	{
		int lca=calLCA(seq[i],st[tp]);
		while(dpt[st[tp-1]]>dpt[lca]) {addEdge(st[tp-1],st[tp]);tp--;}
		addEdge(lca,st[tp]);tp--;
		if(st[tp]!=lca) st[++tp]=lca;
		if(st[tp]!=seq[i]) st[++tp]=seq[i];
	}
	while(--tp) addEdge(st[tp],st[tp+1]);
}

void trDP(int u)
{
	f[u]=mnv[u];
	ll sum=0;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		trDP(v);
		sum+=f[v];
	}G[u]=0;
	if(sum==0)f[u]=mnv[u];
	else if(sum<=f[u])f[u]=sum;
}

int main()
{
	int i;
	scanf("%d",&N);
	for(i=1;i<N;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);
	}
	mnv[rt]=INF;dfs(rt);
	memset(G,0,sizeof G);
	scanf("%d",&M);
	while(M--)
	{
		scanf("%d",&K);
        for(i=1;i<=K;i++) scanf("%d",seq+i);
        buildGraph();
        trDP(rt);
        printf("%lld\n",f[rt]);
    }
    return 0;
}
