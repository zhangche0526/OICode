#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;

const int MAXV=1e5+5,MAXE=1e6+5,INF=1061109567;

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

const int MAXN=45;

int P,Q,R,D;
int id[MAXN][MAXN][MAXN],idcnt;
int W[MAXN][MAXN][MAXN];

inline void buildGraph()
{
	int x,y,z;S=id[P][Q][R]+1,T=S+1;
	for(y=1;y<=Q;y++) for(x=1;x<=P;x++)
		addEdge(S,id[x][y][0],INF),addEdge(id[x][y][R],T,INF);
	for(z=1;z<=R;z++) for(y=1;y<=Q;y++) for(x=1;x<=P;x++)
	{
		addEdge(id[x][y][z-1],id[x][y][z],W[x][y][z]);
		if(z>D)
		{
			if(x>1) addEdge(id[x][y][z],id[x-1][y][z-D],INF);
			if(x<P) addEdge(id[x][y][z],id[x+1][y][z-D],INF);
			if(y>1) addEdge(id[x][y][z],id[x][y-1][z-D],INF);
			if(y<Q) addEdge(id[x][y][z],id[x][y+1][z-D],INF);
		}
	}
}

int main()
{
	scanf("%d%d%d%d",&P,&Q,&R,&D);
	int x,y,z;
	for(z=0;z<=R;z++) for(y=1;y<=Q;y++) for(x=1;x<=P;x++)
	{
		id[x][y][z]=++idcnt;
		if(z) scanf("%d",&W[x][y][z]);
	}
	buildGraph();
	printf("%d",maxFlow());
	return 0;
}
