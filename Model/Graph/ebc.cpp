#include<iostream>
#include<cstdio>

const int MAXV,MAXE;

struct E{int next,to;} e[MAXE];int ecnt,G[MAXV];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);} 

int low[MAXV],dfn[MAXE],dcnt;
bool isBrg[MAXE];

void tarjan(int u,int fa)
{
	int i;low[u]=dfn[u]=++dcnt;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			dfs(v,u);
			low[u]=std::min(low[u],low[v]);
			if(low[v]>=dfn[u]) isBrg[i]=true;
		}else if(dfn[v]<dfn[u]&&v!=fa) low[u]=std::min(low[u],dfn[v]);
	}
}
