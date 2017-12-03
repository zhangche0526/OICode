/*
ID:zhangch33
Task:schlnet
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<stack>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
using namespace std;

const int MAXN=100,MAXM=10000;

int N;

struct E{int from,to,next;} e[MAXM+1];int ecnt,G[MAXN+1];
void addEdge(int u,int v){e[++ecnt]=(E){u,v,G[u]};G[u]=ecnt;}

int gcnt,belong[MAXN+1];//缩成的点数，这个点属于所点后的那个点

stack<int> st;bool inSt[MAXN+1];
int dfn[MAXN+1],low[MAXN+1];int vcnt;
void tarjan(int u)
{
	int i;
	dfn[u]=low[u]=++vcnt;
	st.push(u);inSt[u]=true;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else 
			if(inSt[v])
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
		}
		while(dfn[u]!=low[u]);
	}
}

int inDgr[MAXN+1],outDgr[MAXN+1];

int main()
{
	freopen("schlnet.in","r",stdin);
	freopen("schlnet.out","w",stdout);
	int i;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		int u=i,v;
		scanf("%d",&v);
		while(v)
		{
			addEdge(u,v);
			scanf("%d",&v);
		}
	}
	for(i=1;i<=N;i++)
		if(!dfn[i]) tarjan(i);
	for(i=1;i<=ecnt;i++)
		if(belong[e[i].from]!=belong[e[i].to])
		{
			++inDgr[belong[e[i].to]];
			++outDgr[belong[e[i].from]];
		}
	int ansA=0,ansB=0;
	for(i=1;i<=gcnt;i++)
	{
		if(inDgr[i]) ++ansA;
		if(outDgr[i]) ++ansB;
	}
	ansB=max(ansA,ansB);
	if(gcnt==1) printf("1\n0\n");
	else printf("%d\n%d\n",ansA,ansB);
	return 0;
}
