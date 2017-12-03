#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
typedef long long ll;
using namespace std;

const int MAXN=1e5+5,MAXM=5e5,INF=~0U>>1;

int n,m;

struct E{int next,to,cap;} e[MAXM<<1];
int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}
ll nodeFlow[MAXN];

int dfn[MAXN];
queue<int> que;
bool calDfn(int S,int T)
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
ll calF(int u,int T,ll f)
{
	if(u==T) return f;
	for(int & i=iter[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(e[i].cap>0&&dfn[v]==dfn[u]+1)
		{
			ll res=calF(v,T,min(f,(ll)e[i].cap));
			if(res>0)
			{
				e[i].cap-=res,e[i^1].cap+=res;
				return res;
			}
		}
	}
	return 0;
}

ll dinic(int S,int T)
{
	int i;ll f,res=0;
	while(calDfn(S,T))
	{
		for(i=1;i<MAXN;i++) iter[i]=G[i];
		while((f=calF(S,T,INF))>0) res+=f;
	}
	return res;
}

int main()
{
	freopen("data.in","r",stdin);
	int i,s,t,S,T;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	S=n+1,T=n+2;
	for(i=1;i<=m;i++) 
	{
		int u,v,l,r;scanf("%d%d%d%d",&u,&v,&l,&r);
		addEdge(u,v,r-l);
		nodeFlow[u]-=l,nodeFlow[v]+=l;
	}
	ll flowSum=0;
	for(i=1;i<=n;i++)
	{
		if(nodeFlow[i]>0) addEdge(S,i,nodeFlow[i]),flowSum+=nodeFlow[i];
		else if(nodeFlow[i]<0) addEdge(i,T,-nodeFlow[i]);
	}
	ll f1=dinic(S,T);
	addEdge(t,s,INF);
	ll f2=dinic(S,T);
	if(f1+f2==flowSum) printf("%lld\n",f2);
	else printf("please go home to sleep\n");
	return 0;
}
