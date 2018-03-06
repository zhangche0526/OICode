#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;

const int MAXV=1e5+5,MAXE=2e5+5,INF=1061109567;
int S,T;
struct E{int next,to,cap;} e[MAXE<<1];int ecnt=1,G[MAXV];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}

std::queue<int> que;
int dpt[MAXV];
bool calDpt()
{
	memset(dpt,-1,sizeof dpt);
	dpt[S]=0,que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
		{
			int v=e[i].to;
			if(~dpt[v]) continue;
			dpt[v]=dpt[u]+1;
			que.push(v);
		}
	}
	return ~dpt[T];
}

int iter[MAXV];
int calF(int u,int f)
{
	if(u==T) return f;
	for(int &i=iter[u];i;i=e[i].next) if(e[i].cap>0)
	{
		int v=e[i].to;
		if(dpt[v]!=dpt[u]+1) continue;
		int res=calF(v,min(f,e[i].cap));
		if(res)
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
	while(calDpt())
	{
		memcpy(iter,G,sizeof G);
		while(f=calF(S,INF)) res+=f;
	}
	return res;
}

const int MAXN=105;

int n,m;
int id[MAXN][MAXN],ncnt;

int main()
{
	int i,j,x;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
		id[i][j]=++ncnt;
	int ans=0;S=++ncnt;T=++ncnt;
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
	{
		scanf("%d",&x);ans+=x;
		addEdge(S,id[i][j],x);
	}
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
	{
		scanf("%d",&x);ans+=x;
		addEdge(id[i][j],T,x);
	}
	for(i=1;i<n;i++) for(j=1;j<=m;j++)
	{
		scanf("%d",&x);++ncnt;ans+=x;
		addEdge(ncnt,id[i][j],INF);
		addEdge(ncnt,id[i+1][j],INF);
		addEdge(S,ncnt,x);
	}
	for(i=1;i<n;i++) for(j=1;j<=m;j++)
	{
		scanf("%d",&x);++ncnt;ans+=x;
		addEdge(id[i][j],ncnt,INF);
		addEdge(id[i+1][j],ncnt,INF);
		addEdge(ncnt,T,x);
	}
	for(i=1;i<=n;i++) for(j=1;j<m;j++)
	{
		scanf("%d",&x);++ncnt;ans+=x;
		addEdge(ncnt,id[i][j],INF);
		addEdge(ncnt,id[i][j+1],INF);
		addEdge(S,ncnt,x);
	}
	for(i=1;i<=n;i++) for(j=1;j<m;j++)
	{
		scanf("%d",&x);++ncnt;ans+=x;
		addEdge(id[i][j],ncnt,INF);
		addEdge(id[i][j+1],ncnt,INF);
		addEdge(ncnt,T,x);
	}
	printf("%d",ans-maxFlow());
	return 0;
}
