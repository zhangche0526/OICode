struct E{int to,next,value;} e[MAXM+1];int ecnt,G[MAXN+1];
void addEdge(int u,int v,int w){e[++ecnt]={v,G[u],w};G[u]=ecnt;}

bool inQ[MAXN];int dis[MAXN];

queue<int> que;
void SPFA(int v0)
{
	std::fill(dis+1,dis+1+N,INF);
	dis[v0]=0;		
	inQ[v0]=true;
	que.push(v0);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		inQ[u]=false;
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(dis[v]>dis[u]+edge[i].value)
			{
				dis[v]=dis[u]+edge[i].value;
				if(!inQ[v])//如果以在队列里就不必再入队
				{
					inQ[v]=true;
					que.push(v);
				}
			}
		}
	}
}
