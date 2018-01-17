#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;

const int MAXN=305,MAXM=MAXN*MAXN,INF=1061109567;

int S,T;
struct E{int next,to,cap;} e[MAXM<<1];int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}

std::queue<int> que;
int dpt[MAXN];
bool calDpt()
{
	memset(dpt,-1,sizeof dpt);
	que.push(S);dpt[S]=0;
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

int iter[MAXN];
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

int n,m;
bool opp[MAXN];

int main()
{
	int i;
	scanf("%d%d",&n,&m);S=n+1,T=n+2;
	for(i=1;i<=n;i++) scanf("%d",opp+i);
	for(i=1;i<=n;i++)
		if(opp[i]) addEdge(i,T,1);
		else addEdge(S,i,1);
	for(i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		if(opp[u]==opp[v]) continue;
		if(opp[u]) std::swap(u,v);
		addEdge(u,v,1);
	}
	printf("%d",maxFlow());
	return 0;
}
