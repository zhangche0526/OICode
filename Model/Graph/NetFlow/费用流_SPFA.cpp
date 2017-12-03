#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int MAXN=5005,MAXM=50005,INF=~0U>>1;

int N,M,S,T;

int minCost,maxFlow;

struct E{int next,to,cap,cost;} e[MAXM<<1];
int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c,int w)
{
	e[++ecnt]=(E){G[u],v,c,w};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0,-w};G[v]=ecnt;
}

int pre[MAXN];//pre:����·����ı�

int dis[MAXN];bool inQ[MAXN];
queue<int> que;
bool SPFA()
{
	int i;
	for(i=1;i<=N;i++) dis[i]=INF;
	memset(inQ,false,sizeof(inQ));
	inQ[S]=true,dis[S]=0;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(e[i].cap>0&&dis[v]>dis[u]+e[i].cost)
			{
				dis[v]=dis[u]+e[i].cost;
				pre[v]=i;
				if(!inQ[v])
				{
					inQ[v]=true;
					que.push(v);
				}
			}
		}
		inQ[u]=false;
	}
	return dis[T]!=INF;
}

void calc()
{
	int f=INF,u;
	for(u=T;u!=S;u=e[pre[u]^1].to) f=min(f,e[pre[u]].cap);
	for(u=T;u!=S;u=e[pre[u]^1].to) e[pre[u]].cap-=f,e[pre[u]^1].cap+=f;
	minCost+=f*dis[T];
	maxFlow+=f;
}

int main()
{
	int i;
	scanf("%d%d%d%d",&N,&M,&S,&T);
	for(i=1;i<=M;i++)
	{
		int u,v,c,w;scanf("%d%d%d%d",&u,&v,&c,&w);
		addEdge(u,v,c,w);
	}
	while(SPFA()) calc();
	printf("%d %d\n",maxFlow,minCost);
	return 0;
}
