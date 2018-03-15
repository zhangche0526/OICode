#include<queue>
struct E{int to,next,value;} e[MAXM];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]={v,G[u],w};G[u]=ecnt;}

struct HN{int id,v;};
bool operator <(const HN &a,const HN &b){a.v>b.v;}

priority_queue<HN> heap;

bool inS[MAXN];int dis[MAXN];

void dijkstra(int v0)
{
	int i;std::fill(dis+1,dis+N+1,INF);
	dis[v0]=0;heap.push((HN){v0,0});
	while(!heap.empty())
	{	
		int u=heap.top().id;heap.pop();
		if(inS[u]) continue;inS[u]=true;
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(inS[v]) continue;
			if(dis[v]>dis[u]+e[i].value)
			{
				dis[v]=dis[u]+e[i].value;
				heap.push((HN){v,dis[v]});
			}
		}
	}
}
