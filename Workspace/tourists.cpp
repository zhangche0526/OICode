#include<iostream>
#include<cstdio>
#include<stack>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}

const int MAXN=1e5+5;

int N,M,Q,ncnt;

int W[MAXN<<1];

struct E{int next,to;} E[MAXN<<2];int ecnt,G[MAXN],T[MAXN<<1];
void addEdge(int *G,int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int *G,int u,int v){addEdge(G,u,v);addEdge(G,v,u);}
struct A{int u,v;};

int dfn[MAXN],dcnt,low[MAXN];

std::stack<A> st;
int tarjan(int u,int la)
{
	low[u]=dfn[u]=++dcnt;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(dfn[v]) continue;
		st.push((A){u,v});
		umn(low[u],low[v]);
		if(low[v]>=dfn[u])
		{
			ncnt++;
			addEdge2(T,u,v);
			
		}
	}
}

int main()
{
	int i;scanf("%d%d%d",&N,&M,&Q);
	for(i=1;i<=N;i++) scanf("%d",W+i);
	for(i=1;i<=M;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(G,u,v);
	}
	buildTree();
	return 0;
}
