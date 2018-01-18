#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;

const int MAXV=500,MAXE=6e4,INF=1061109567;

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
	dpt[S]=0;que.push(S);
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
	while(calDpt())
	{
		memcpy(iter,G,sizeof G);
		while(f=calF(S,INF)) res+=f;
	}
	return res;
}

int n,m,s,t;

int main()
{
	int i,w;scanf("%d%d%d%d",&n,&m,&s,&t);
	S=n+1<<1,T=S+1;addEdge(S,s<<1,INF);addEdge(t<<1|1,T,INF);
	for(i=1;i<=n;i++){scanf("%d",&w);addEdge(i<<1,i<<1|1,w);}
	for(i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge(u<<1|1,v<<1,INF);
		addEdge(v<<1|1,u<<1,INF);
	}
	printf("%d",maxFlow());
	return 0;
}
