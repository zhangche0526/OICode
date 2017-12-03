#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#define min(a,b) (a<b?a:b)
using namespace std;

const int MAXN=205,MAXM=40010,INF=~0U>>1;

int n,m,S,T;
int lower[MAXM],nodeFlow[MAXN];//in:+ out:-
int ans[MAXM];
struct E{int next,to,cap,id;} e[MAXM<<1];
int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c,int id)
{
	e[++ecnt]=(E){G[u],v,c,id};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0,0};G[v]=ecnt;
}
int dfn[MAXN];
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
int iter[MAXN];
int calF(int u,int f)
{
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
void dinic()
{
	while(calDfn())
	{
		for(int i=1;i<=T;i++) iter[i]=G[i];
		while(calF(S,INF)>0);
	}
}
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	int i,u,v,l,r;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&u,&v,&l,&r);
		addEdge(u,v,r-l,i);
		lower[i]=l,nodeFlow[u]-=l,nodeFlow[v]+=l;
	}
	S=n+1,T=n+2;
	for(i=1;i<=n;i++)
	{
		if(nodeFlow[i]>0) addEdge(S,i,nodeFlow[i],0);
		else if(nodeFlow[i]<0) addEdge(i,T,-nodeFlow[i],0);
	}
	dinic();
	bool ok=true;
	for(i=G[S];i;i=e[i].next)
		if(e[i].cap>0) {ok=false;break;}
	if(ok)
	{
		printf("YES\n");
		for(i=2;i<=ecnt;i++)
			ans[e[i].id]=e[i^1].cap;
		for(i=1;i<=m;i++) printf("%d\n",ans[i]+lower[i]);
	}else printf("NO\n");
	return 0;
}
