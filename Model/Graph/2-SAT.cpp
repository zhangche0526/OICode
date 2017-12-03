#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>

const int MAXN=16e3+5,MAXM=2e4+5;

int N,M;

class CFS
{
	public:
		struct E{int next,fr,to;} e[MAXM<<1];int ecnt,G[MAXN];
		void addEdge(int u,int v){e[++ecnt]=(E){G[u],u,v};G[u]=ecnt;}
} G1,G2;

int belong[MAXN],scnt,dfn[MAXN],dcnt,low[MAXN];
std::stack<int> st;bool inSt[MAXN];
void tarjan(int u)
{
	int i;
	low[u]=dfn[u]=++dcnt;
	st.push(u);inSt[u]=true;
	for(i=G1.G[u];i;i=G1.e[i].next)
	{
		int v=G1.e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=std::min(low[u],low[v]);
		}else if(inSt[v]) 
			low[u]=std::min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++scnt;
		int t;
		do
		{
			t=st.top();st.pop();
			belong[t]=scnt,inSt[t]=false;
		}while(t!=u);
	}
}

int oppGr[MAXN],inDgr[MAXN],typ[MAXN];

std::queue<int> que;
inline void topoSort()
{
	int i;
	for(i=1;i<=scnt;i++)
		if(!inDgr[i]) que.push(i);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		if(typ[u]) continue;
		typ[u]=1,typ[oppGr[u]]=2;
		for(i=G2.G[u];i;i=G2.e[i].next)
			if(--inDgr[G2.e[i].to]==0)
				que.push(G2.e[i].to);
	}
}
int main()
{
	int i;
	scanf("%d%d",&N,&M);
	for(i=1;i<=M;i++)
	{
		int u,v;scanf("%d%d",&u,&v);u--,v--;
		G1.addEdge(u,v^1);G1.addEdge(v,u^1);
	}
	for(i=0;i<(N<<1);i++)
		if(!dfn[i]) tarjan(i);
	for(i=0;i<N;i++)
		if(belong[i<<1]^belong[(i<<1)|1])
			oppGr[belong[i<<1]]=belong[(i<<1)|1],
			oppGr[belong[(i<<1)|1]]=belong[i<<1];
		else{printf("NIE\n");return 0;}
	for(i=1;i<=G1.ecnt;i++)
		if(belong[G1.e[i].fr]^belong[G1.e[i].to])
		{
			G2.addEdge(belong[G1.e[i].to],belong[G1.e[i].fr]);
			++inDgr[belong[G1.e[i].fr]];
		}
	topoSort();
	for(i=0;i<(N<<1);i++)
		if(typ[belong[i]]&1)
			printf("%d\n",i+1);
	return 0;
}
