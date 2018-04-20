#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long ll;
const int MAXN=1505,MAXM=5005,P=1e9+7,INF=1061109567;

inline int add(int a,int b){return (a+b)%P;}
inline void uadd(int &a,int b){a=add(a,b);}
inline int mul(int a,int b){return a*b%P;}

int n,m;
int ans[MAXM];

struct E{int next,fr,to,val;} e[MAXM];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],u,v,w};G[u]=ecnt;}

struct HN{int id,v;};
bool operator >(const HN &a,const HN &b){return a.v>b.v;}
std::priority_queue<HN,std::vector<HN>,std::greater<HN> > heap;
bool inS[MAXN];int dis[MAXN];
inline void dijkstra(int S)
{
	memset(dis,0x3f,sizeof dis);
	memset(inS,false,sizeof inS);
	dis[S]=0;heap.push((HN){S,dis[S]});
	while(!heap.empty())
	{
		int u=heap.top().id;heap.pop();
		if(inS[u]) continue;inS[u]=true;
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(inS[v]) continue;
			if(dis[u]+e[i].val<dis[v])
			{
				dis[v]=dis[u]+e[i].val;
				heap.push((HN){v,dis[v]});
			}
		}
	}
}

int inDgr[MAXN];bool inSP[MAXM];
int seq[MAXN],scnt;
std::queue<int> que;
inline void toposort(int S)
{
	scnt=0;
	memset(inDgr,0,sizeof inDgr);
	memset(inSP,false,sizeof inSP);
	for(int i=1;i<=m;i++)
		inDgr[e[i].to]+=inSP[i]= dis[e[i].fr]+e[i].val==dis[e[i].to];
	que.push(S),seq[++scnt]=S;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(inSP[i])
		{
			int v=e[i].to;
			if(--inDgr[v]==0) que.push(v),seq[++scnt]=v;
		}
	}
}

int f[MAXN],g[MAXN];
inline void topoDP(int S)
{
	memset(f,0,sizeof f);
	memset(g,0,sizeof g);
	f[S]=1;
	for(int *u=seq+1;u<=seq+scnt;u++)
		for(int i=G[*u];i;i=e[i].next) if(inSP[i])
		{
			int v=e[i].to;
			uadd(f[v],f[*u]);
		}
	for(int *u=seq+scnt;u>=seq+1;u--)
	{
		g[*u]++;
		for(int i=G[*u];i;i=e[i].next) if(inSP[i])
		{
			int v=e[i].to;
			uadd(g[*u],g[v]);
		}
	}
	for(int i=1;i<=m;i++) if(inSP[i]) uadd(ans[i],mul(f[e[i].fr],g[e[i].to]));
}

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
	}
	for(i=1;i<=n;i++)
	{
		dijkstra(i);
		toposort(i);
		topoDP(i);
	}
	for(i=1;i<=m;i++) printf("%d\n",ans[i]);
	return 0;
}
/*
4 4
1 2 5
2 3 5
3 4 5
1 4 8
*/
/*
4 6
1 2 2
1 3 5
2 3 3
4 3 2
2 4 1
1 4 4
*/
