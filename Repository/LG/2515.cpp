#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;

const int MAXN=100,MAXE=10000,MAXM=500;

int M,N;

struct E{int from,to,next;};
struct CFS//Chain Forward Star
{
	E e[MAXE+1];
	int ecnt,G[MAXN+1];
	void addEdge(int u,int v){e[++ecnt]=(E){u,v,G[u]};G[u]=ecnt;}
} G1,G2;

int weight[MAXN+1],value[MAXN+1];

stack<int> st;bool inSt[MAXN+1];
int dfn[MAXN+1],low[MAXN+1],times;
int belong[MAXN+1];
struct S{int w,v;} scc[MAXN+1];int scnt;
void tarjan(int u)
{
	int i;
	dfn[u]=low[u]=++times;
	inSt[u]=true;
	for(i=G1.G[i];i;i=G1.e[i].next)
	{
		int v=G1.e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else
			if(inSt[v])
				low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++scnt;
		do
		{
			u=st.top();st.pop();
			inSt[u]=false;
			belong[u]=scnt;
			scc[scnt]={weight[u],value[u]};
		}
		while(low[u]!=dfn[u]);
	}
}

bool inDgr[MAXN+1];

inline void rebuild()
{
	int i;
	for(i=1;i<=G1.ecnt;i++)
		if(belong[G1.e[i].from]!=belong[G1.e[i].to])
		{
			G2.addEdge(belongG1.e[i].from],belong[G1.e[i].to]);
			inDgr[belong[G1.e[i].to]]=true;
		}
}

int dp[MAXN+1][MAXM+1];

void dfs(int u)
{
	int i,j,k;
	//dfs过程
	for(i=G2.G[u];i;i=G2.e[i].next)
	{
		dfs(G2.e[i].to);
		for(j=M-scc[u].w;j>=0;j--)
			for(k=0;k<=j;k++)
				dp[u][j]=max(dp[u][j],dp[u][k]+dp[G2.e[i].to][j-k]);
	}
	//更新本节点的值
	for(i=M;i>=0;i--)
		if(i>=scc[u].w)
			dp[u][i]=dp[u][j-scc[u].w]+scc[u].v;
		else dp[u][i]=0;
	//
}

int main()
{
	int i;
	scanf("%d%d",&N,&M);
	for(i=1;i<=N;i++)
		scanf("%d",&weight[i]);
	for(i=1;i<=N;i++)
		scanf("%d",&value[i]);
	for(i=1;i<=N;i++)
	{
		int u=i,v;
		scanf("%d",&v);
		while(v)
		{
			G1.addEdge(u,v);
			scanf("%d",&v);
		}
	}
	for(i=1;i<=n;i++)
		if(!dfn[i]) tarjan(i);
	rebuild();
	//
	for(i=1;i<=scnt;i++)
		if(!inDgr[i])
		{
			inDgr[i]=true;
			G2.addEdge(0,i);
		}
	dfs(0);
	printf("%d\n",dp[0][M]);
	return 0;
}
