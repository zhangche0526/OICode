#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;

const int MAXV=205,MAXE=MAXV*MAXV,INF=~0U>>1;

int n,n1,S,T;
struct E{int next,to,cap;} e[MAXE<<1];
int ecnt=1,G[MAXV];
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
}

int maxFlow()
{
	int i,res=0;
	while(calDfn())
	{
		int f;for(i=1;i<=T;i++) iter[i]=G[i];
		while((f=calF(S,INF))>0)
			res+=f;
	}
	return res;
}

int main()
{
	freopen("flyer.in","r",stdin);
	freopen("flyer.out","w",stdout);
	int i,a,b;
	scanf("%d%d",&n,&n1);
	S=n+1,T=n+2;
	for(i=1;i<=n1;i++) addEdge(S,i,1);
	for(i=n1+1;i<=n;i++) addEdge(i,T,1);
	while(scanf("%d%d",&a,&b)!=EOF) addEdge(a,b,1);
	printf("%d\n",maxFlow());
	return 0;
}

