#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=1e4+5,MAXM=MAXN<<1;

struct E{int next,to,val;}e[MAXM];int G[MAXN],ecnt;
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}

int n,k,vis[MAXN],ans,rt,num;

int mx[MAXN],sz[MAXN],min,dis[MAXN];
void calSz(int u,int fa)//处理子树的大小  
{
	sz[u]=1;mx[u]=0;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=fa&&!vis[v])
		{
			calSz(v,u);
			sz[u]+=sz[v];
			mx[u]=std::max(mx[u],sz[v]);
		}
	}
}

void calRt(int r,int u,int fa)//求重心  
{
	mx[u]=std::max(mx[u],sz[r]-sz[u]);
	if(mx[u]<min) min=mx[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=fa&&!vis[v])calRt(r,v,u);
	}
}

void calDis(int u,int d,int fa)//求距离  
{
	dis[++num]=d;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=fa&&!vis[v]) calDis(v,d+e[i].val,u);
	}
}

int calc(int u,int d)//求点对个数
{
	int res=0;num=0;
	calDis(u,d,0);
	std::sort(dis+1,dis+num+1);
	int i=1,j=num;
	while(i<j)//经典  
	{
		while(dis[i]+dis[j]>k&&i<j)j--;
		res+=j-i;i++;
	}
	return res;
}

void dc(int u)
{
	min=n;calSz(u,0);calRt(u,u,0);
	ans+=calc(rt,0);vis[rt]=true;
	for(int i=G[rt];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!vis[v])
		{
			ans-=calc(v,e[i].val);
			dc(v);
		}
	}
}

int main()
{
	while(scanf("%d%d",&n,&k)&&n&&k)
	{
		memset(vis,0,sizeof(vis));
		memset(G,0,sizeof(G));
		ecnt=ans=0;
		int u,v,w;
		for(int i=1;i<n;i++)
		{
			scanf("%d%d%d",&u,&v,&w);
			addEdge(u,v,w);
			addEdge(v,u,w);
		}
		dc(1);
		printf("%d\n",ans);
	}
	return 0;
}

