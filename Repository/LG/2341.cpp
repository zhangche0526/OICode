#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;

const int MAXN=1000,MAXM=5000;

int N,M;

struct E{int from,to,next;} e[MAXM+1];int ecnt,G[MAXN+1];
void addEdge(int u,int v){e[++ecnt]=(E){u,v,G[u]};G[u]=ecnt;}

stack<int> st;
bool inSt[MAXN+1];
int belong[MAXN+1],gcnt,memNum[MAXN+1];

int dfn[MAXN+1],low[MAXN+1];
int vcnt;
void tarjan(int u)
{
	int i;
	dfn[u]=low[u]=++vcnt;
	st.push(u);inST[u]=true;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else 
			if(inst[v])
				low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		++gcnt;
		do
		{
			u=st.top();st.pop();
			inSt[u]=false;
			belong[u]=gcnt;
			++memNum[gcnt];
		}while(low[u]!=dfn[u]);
	}
}

int outDgr[MAXN+1];

int main()
{
	int i;
	scanf("%d%d",&N,&M);
	for(i=1;i<=m;i++)
	{
			int u,v;
			scanf("%d%d",&u,&v);
			addEdge(u,v);
	}
	for(i=1;i<=N;i++)
			if(!dfn[i]) tarjan(i);
	for(i=1;i<=M;i++)
			if(belong[e[i].from]!=belong[e[i].to])
					++outDgr[e[i].to];
	int ans;
	bool exist=false;
	for(i=1;i<=gcnt;i++)
			if(!outDgr[i])
					if(exist)
					{
							exist=false;
							break;
					}else exist=true,ans=i;
	if(exist) printf("%d\n",memNum[ans]);
	else printf("0\n");
	return 0;
}
