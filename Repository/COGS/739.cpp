#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int MAXV=205,MAXE=MAXV*(MAXV+2),INF=~0U>>1;

int n,m,S,T;
int minCost;
struct E{int next,to,cap,cost;};
struct CFS
{
	E e[MAXE<<1];
	int ecnt,G[MAXV];
	void addEdge(int u,int v,int c,int w)
	{
		e[++ecnt]=(E){G[u],v,c,w};G[u]=ecnt;
		e[++ecnt]=(E){G[v],u,0,-w};G[v]=ecnt;
	}
	CFS(){ecnt=1;}
} G[2];
int pre[MAXV];

bool inQ[MAXV];int dis[MAXV];queue<int> que;
bool SPFA(int flag)
{
	CFS & rG=G[flag>0];
	int i;
	memset(inQ,false,sizeof(inQ));
	for(i=1;i<=m+n+1;i++) dis[i]=INF;
	dis[S]=0;que.push(S);inQ[S]=true;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		inQ[u]=false;
		for(i=rG.G[u];i;i=rG.e[i].next)
		{
			int v=rG.e[i].to;
			if(rG.e[i].cap>0&&dis[v]>dis[u]+rG.e[i].cost*flag)
			{
				dis[v]=dis[u]+rG.e[i].cost*flag;
				pre[v]=i;
				if(!inQ[v]) inQ[v]=true,que.push(v);
			}
		}
	}
	return dis[T]!=INF;
}

void calc(int flag)
{
	CFS & rG=G[flag>0];
	int f=INF,u;
	for(u=T;u!=S;u=rG.e[pre[u]^1].to) 
		f=min(f,rG.e[pre[u]].cap);
	for(u=T;u!=S;u=rG.e[pre[u]^1].to) 
		rG.e[pre[u]].cap-=f,rG.e[pre[u]^1].cap+=f;
	minCost+=f*dis[T];
}

int main()
{
	freopen("tran.in","r",stdin);
	freopen("tran.out","w",stdout);
	int i,j,c,w;
	scanf("%d%d",&m,&n);
	S=0,T=n+m+1;
	//
	for(i=1;i<=m;i++)
		scanf("%d",&c),G[1].addEdge(S,i,c,0);
	for(i=1;i<=n;i++)
		scanf("%d",&c),G[1].addEdge(i+m,T,c,0);
	for(i=1;i<=m;i++)
		for(j=1;j<=n;j++)
			scanf("%d",&w),G[1].addEdge(i,j+m,INF,w);
	G[0]=G[1];
	//
	minCost=0;
	while(SPFA(1)) 
		calc(1);
	printf("%d\n",minCost);
	minCost=0;
	while(SPFA(-1))
		calc(-1);
	printf("%d\n",-minCost);
	return 0;
}
