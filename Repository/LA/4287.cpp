#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>

const int MAXN=2e4+5,MAXM=5e4+4;

int n,m;

struct E{int next,to;} e[MAXM];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}

int scnt,inDgr[MAXN],outDgr[MAXN],belong[MAXN];

int low[MAXN],dfn[MAXN],dcnt;
std::stack<int> st;bool inSt[MAXN];
void tarjan(int u)
{
	low[u]=dfn[u]=++dcnt;
	st.push(u);inSt[u]=true;
	for(i=G[u];i;i=e[i].next)
	{
		int v;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=std::min(low[u],low[v]);
		}
		else if(inSt[v]) low[u]=std::min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++scnt;
		int t;
		do
		{
			t=st.top();st.pop();inSt[t]=false;
			belong[t]=scnt;
		}while(t!=u);
	}
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i;
		scanf("%d%d",&n,&m);
		memset(G,0,sizeof(G));ecnt=0;
		for(i=1;i<=m;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			addEdge(u,v);
		}
		memset(dfn,0,sizeof(dfn));memset(inDgr,0,sizeof(inDgr));
		memset(outDgr,0,sizeof(outDgr));scnt=0;
	}
	return 0;
}
