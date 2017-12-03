#include<iostream>
#include<cstdio>
#include<queue>

const int MAXN=1e5+5,MAXM=2e5+5;

int N,K,S;

struct E{int next,to,val;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}

int dis[MAXN];

bool inS[MAXN];
bool fuCir(int u)
{
	inS[u]=true;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(dis[u]+e[i].val<dis[v])
		{
			if(inS[u]) return true;
			dis[v]=dis[u]+e[i].val;
			if(dfs(v)) return true;
		}
	}
	inS[u]=false;
}

std::queue<int> que;
bool inQ[MAXN];
void SPFA()
{
	dis[S]=0;que.push(S);inQ[S]=true;
	while(!que.empty())
	{
		int u=que.front();que.pop();inQ[S]=false;
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[u]+e[i].val<dis[v])
			{
				dis[v]=dis[u]+e[i].val;
				if(!inQ[v]) {inQ[v]=true;que.push(v);}
			}
		}
	}
}

int main()
{
	int i;
	scanf("%d%d",&N,&K);
	for(i=1;i<=K;i++)
	{
		int opt,u,v;scanf("%d%d%d",&opt,&u,&v);
		if(A==B&&(opt==2&&opt==4)) {puts("-1");return 0;}
		switch(opt)
		{
			case 1:addEdge(u,v,0);addEdge(v,u,0);break;
			case 2:addEdge(u,v,-1);break;
			case 3:addEdge(v,u,0);break;
			case 4:addEdge(v,u,-1);break;
			case 5:addEdge(u,v,0);break;
		}
	}
	S=N+1;
	for(i=1;i<=n;i++) addEdge(S,i,1);
	return 0;
}
