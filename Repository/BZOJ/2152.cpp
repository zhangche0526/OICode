#include<iostream>
#include<cstdio>
#include<algorithm>

const int MAXN=2e4+5,MAXM=MAXN<<1;

struct E{int next,to,val;} e[MAXM];int G[MAXN],ecnt;
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}

int n;
int ans,rt,min,num,mx[MAXN],sz[MAXN],vis[MAXN],dis[MAXN];

void calSz(int u,int fa)
{
	sz[u]=1,mx[u]=0;
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
	if(min>mx[u]) min=mx[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v!=fa&&!vis[v]) calRt(r,v,u);
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

int cnt3[3];
int calc(int u,int d)
{
	num=0;
	calDis(u,d,0);
	for(int i=0;i<3;i++) cnt3[i]=0;
	for(int i=1;i<=num;i++) cnt3[dis[i]%3]++;
	return cnt3[0]*cnt3[0]+cnt3[1]*cnt3[2]*2;
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
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge(u,v,w);addEdge(v,u,w);
	}
	dc(1);
	int a=ans,b=n*n;
	int tmp=std::__gcd(a,b);
	printf("%d/%d\n",a/tmp,b/tmp);
}
