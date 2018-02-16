#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int MAXN=1e4+5,MAXM=MAXN<<1,MAXQ=105;

int n,q;
int qry[MAXQ],ans[MAXQ];
struct E{int next,to,val;}e[MAXM];int G[MAXN],ecnt;
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}

int vis[MAXN],rt;

int mx[MAXN],sz[MAXN],min,dis[MAXN],num;
void calSz(int u,int fa)
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

void calRt(int r,int u,int fa)
{
	mx[u]=std::max(mx[u],sz[r]-sz[u]);
	if(mx[u]<min) min=mx[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=fa&&!vis[v])calRt(r,v,u);
	}
}

void calDis(int u,int d,int fa)
{
	dis[++num]=d;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=fa&&!vis[v]) calDis(v,d+e[i].val,u);
	}
}

int k;
int calc(int u,int d)
{
	int res0=0,res1=0;num=0;
	calDis(u,d,0);
	std::sort(dis+1,dis+num+1);
	int i=1,j=num;
	while(i<j)
	{
		while(dis[i]+dis[j]>k&&i<j)j--;
		res1+=j-i;i++;
	}
	i=1,j=num;
	while(i<j)
	{
		while(dis[i]+dis[j]>=k&&i<j)j--;
		res0+=j-i;i++;
	}
	return res1-res0;
}

void dc(int u)
{
	min=n;calSz(u,0);calRt(u,u,0);
	for(int i=1;i<=q;i++) 
	{
		k=qry[i];
		ans[i]+=calc(rt,0);
	}
	vis[rt]=true;
	for(int i=G[rt];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!vis[v])
		{
			for(int j=1;j<=q;j++) 
			{
				k=qry[j];
				ans[j]-=calc(v,e[i].val);
			}
			dc(v);
		}
	}
}

int main()
{
	scanf("%d%d",&n,&q);
	int u,v,w;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);
		addEdge(v,u,w);
	}
	for(int i=1;i<=q;i++) scanf("%d",qry+i);
	dc(1);
	for(int i=1;i<=q;i++)
		if(qry[i]) puts(ans[i]?"Yes":"No");
		else puts("Yes");
	return 0;
}
