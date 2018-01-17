#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;

const int MAXV=4e3,MAXE=2e6,INF=1061109567;

int S,T;

struct E{int next,to,cap;} e[MAXE<<1];int ecnt,G[MAXV];
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

const int MAXN=25;

int n,m;int ptot;

int mp[MAXN*MAXN],id[MAXN][MAXN],idcnt;
int did[MAXN*MAXN],dcnt;
int dis[MAXN*MAXN][MAXN<<1];

bool check(int Tm)
{
	ecnt=1,memset(G,0,sizeof G);
	S=n*m+1,T=n*m+2;
	int u,d,t;
	for(u=1;u<=n*m;u++) if(mp[u]==1) addEdge(S,u,1);
	for(u=1;u<=n*m;u++) if(mp[u]==1)
		for(d=1;d<=dcnt;d++) for(t=dis[u][d];t<=Tm;t++)
			addEdge(u,T+d*Tm+t,1);
	for(d=1;d<=dcnt;d++) for(t=1;t<=Tm;t++)
		addEdge(T+d*Tm+t,T,1);
	return maxFlow()==ptot;
}

void bfs(int v0)
{
	int dr=did[v0];
	que.push(v0);dis[v0][dr]=0;
	while(!que.empty())
	{
		int u=que.front(),d=dis[u][dr];que.pop();
		if(mp[u-m]==1&&dis[u-m][dr]==INF) dis[u-m][dr]=d+1,que.push(u-m);
		if(mp[u+m]==1&&dis[u+m][dr]==INF) dis[u+m][dr]=d+1,que.push(u+m);
		if(mp[u-1]==1&&dis[u-1][dr]==INF) dis[u-1][dr]=d+1,que.push(u-1);
		if(mp[u+1]==1&&dis[u+1][dr]==INF) dis[u+1][dr]=d+1,que.push(u+1);
	}
}

int main()
{
	int i,j;char c;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
	{
		id[i][j]=++idcnt;
		do c=getchar();while(c!='.'&&c!='X'&&c!='D');
		if(c=='.') mp[id[i][j]]=1,ptot++;
		if(c=='D') mp[id[i][j]]=-1;
	}

	memset(dis,0x3f,sizeof dis);
	for(int u=1;u<=n*m;u++) if(mp[u]==-1) did[u]=++dcnt,bfs(u);

	for(int u=1;u<=n*m;u++) if(mp[u]==1)
	{
		bool gg=true;
		for(int d=1;d<=dcnt;d++) if(dis[u][d]!=INF) {gg=false;break;}
		if(gg) {puts("impossible");return 0;}
	}

	int l=1,r=n*m;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid-1;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}
/*
5 5
XXXXX
X...D
XX.XX
X..XX
XXDXX
*/
