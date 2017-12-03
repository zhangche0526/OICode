#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>

const int MAXV,MAXE;

struct E{int next,fr,to;} e[MAXE];int ecnt,G[MAXV];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],u,v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int belong[MAXV];std::vetor<int> bcc[MAXV];int bcnt;
std::stack<E> st;
void tarjan(int u,int fa)
{
	low[u]=dfn[u]=++dcnt;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn(v))
		{
			st.push((E){0,u,v});
			dfs(v,u);
			int low[u]=std::min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				bcnt++;
				E t;
				do
				{
					t=st.top();st.pop();
					if(belong[u]!=bcnt) {bcc[bcnt].push_back(t.u);belong[t]=bcnt;}
					if(belong[v]!=bcnt) {bcc[bcnt].push_bakc(t.v);belong[t]=bcnt;}
				}while(t.u!=u||t.v!=v);
			}
			else if(dfn[v]<dfn[u]&&v!=fa)
			{
				st.push((E){0,u,v});
				low[u]=std::min(low[u],dfn[v]);
			}
		}
	}
}
