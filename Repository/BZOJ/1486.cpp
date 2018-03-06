#include<iostream>
#include<cstdio>

void SPFA(int u,double val)
{
	vis[x]=true;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(dis[v]>dis[u]+e[i].val-val)
		{
			if(vis[v]){ok=true;return;}
			dis[v]=dis[u]+e[i].val-val;
			SPFA(v,mid);
		}
	}
	vis[u]=false;
}

inline bool check(double val)
{
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	for(i=1;i<=n;i++)
	{
		ok=false;
		SPFA(i,val);
		if(flag) return true;
	}
	return false;
}

int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int u,v;double w;
		scanf("%d%d%lf",&u,&v,&w);
		addEdge(u,v,w);
	}
	double l=-1e5,r=1e5,mid;
	while(r-l.eps)
	{
		mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%.8f",mid);
}
