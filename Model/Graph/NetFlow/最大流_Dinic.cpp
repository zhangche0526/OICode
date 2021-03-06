#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int MAXN=10005,MAXM=100005,INF=~0U>>1;

int N,M,S,T;

struct E{int next,to,cap;} e[MAXM<<1];
int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}

int dfn[MAXN];
std::queue<int> que;
bool calDfn(int u)
{
	memset(dfn,-1,sizeof dfn);
	dfn[S]=0;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
		{
			int v=e[i].to;
			if(~dfn[v]) continue;
			dfn[v]=dfn[u]+1;
			que.push(v);
		}
	}
	return ~dfn[T];
}

int iter[MAXN];
int calF(int u,int f)
{
	if(u==T) return f;
	for(int &i=iter[u];i;i=e[i].next) if(e[i].cap>0)
	{
		int v=e[i].to;
		if(dfn[v]!=dfn[u]+1) continue;
		int res=calF(v,min(f,e[i].cap));
		if(res>0)
		{
			e[i].cap-=res,e[i^1].cap+=res;
			return res;
		}
	}
	return 0;
}

int maxFlow()
{
	int f,res=0;
	while(calDfn(S))
	{
		memcpy(iter,G,sizeof G);
		while(f=calF(S,INF)) res+=f;
	}
	return res;
}

int main()
{
	int i;
	scanf("%d%d%d%d",&N,&M,&S,&T);
	for(i=1;i<=M;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
	}
	printf("%d",maxFlow());
}
