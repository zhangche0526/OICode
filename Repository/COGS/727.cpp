#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int MAXV=205,MAXE=4e4+205,INF=~0U>>1;

int m,n,S,T;

struct E{int next,to,cap;} e[MAXE<<1];int ecnt=1,G[MAXV];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}

int dfn[MAXV];
queue<int> que;
bool calDfn()
{
	int i;
	memset(dfn,-1,sizeof(dfn));
	dfn[S]=0;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(e[i].cap>0&&dfn[v]==-1)
				dfn[v]=dfn[u]+1,que.push(v);
		}
	}
	return dfn[T]!=-1;
}
int iter[MAXV];
int calF(int u,int f)
{
	int i;
	if(u==T) return f;
	for(int & i=iter[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(e[i].cap>0&&dfn[v]==dfn[u]+1)
		{
			int res=calF(v,min(f,e[i].cap));
			if(res>0)
			{
				e[i].cap-=res,e[i^1].cap+=res;
				return res;
			}
		}
	}
	return 0;
}

int dinic()
{
	int i,f,res=0;
	while(calDfn())
	{
		for(i=1;i<=T;i++) iter[i]=G[i];
		while((f=calF(S,INF))>0) res+=f;
	}
	return res;
}


int main()
{
	freopen("shuttle.in","r",stdin);
	freopen("shuttle.out","w",stdout);
	int i,j,x,sum=0;
	scanf("%d%d",&m,&n);
	S=m+n+1,T=S+1;
	for(i=1;i<=m;i++)
	{
		scanf("%d",&x);addEdge(S,i,x);sum+=x;
		while(getchar()==' ')
			scanf("%d",&x),addEdge(i,x+m,INF);
	}
	for(i=1;i<=n;i++) scanf("%d",&x),addEdge(i+m,T,x);
	int ans=sum-dinic();
	for(i=1;i<=m;i++) if(dfn[i]!=-1) printf("%d ",i);putchar('\n');
	for(i=1;i<=n;i++) if(dfn[i+m]!=-1) printf("%d ",i);putchar('\n');
	printf("%d\n",ans);
	return 0;
}
