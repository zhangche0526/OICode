#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}

const int MAXN=1e4+5,MAXQ=105;

int n,q;
int qry[MAXQ],ans[MAXQ];

struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}

bool vis[MAXN];int rt;
int sz[MAXN],mxv[MAXN],mnv;
void calSz(int u,int la)
{
	sz[u]=1,mxv[u]=0;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calSz(v,u);
		sz[u]+=sz[v];
		umx(mxv[u],sz[v]);
	}
}

void calRt(int r,int u,int la)
{
	umx(mxv[u],sz[r]-sz[u]);
	if(mxv[u]<mnv) mnv=mxv[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calRt(r,v,u);
	}
}

int dis[MAXN],dcnt;
void calDis(int u,int la,int d)
{
	dis[++dcnt]=d;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calDis(v,u,d+e[i].val);
	}
}

int k;
int calc(int u,int d)
{
	int res0=0,res1=0;dcnt=0;
	calDis(u,d,0);
	std::sort(dis+1,dis+dcnt+1);
	int l,r;
	for(l=1,r=dcnt;l<r;l++)
	{
		while(dis[l]+dis[r]>=k&&l<r) r--;
		res0+=r-l;
	}
	for(l=1,r=dcnt;l<r;l++)
	{
		while(dis[l]+dis[r]>k&&l<r) r--;
		res1+=r-l;
	}
	return res1-res0;
}

void dc(int u)
{
	int i,j;mnv=n;
	calSz(u,0);calRt(u,u,0);
	for(i=1;i<=q;i++)
	{
		k=qry[i];
		ans[i]+=calc(rt,0);
	}
	vis[rt]=true;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		for(j=1;j<=q;j++)
		{
			k=qry[j];
			ans[j]-=calc(v,e[i].val);
		}
		dc(v);
	}
}

int main()
{
	int i;scanf("%d%d",&n,&q);
	for(i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);
	}
	for(i=1;i<=q;i++) scanf("%d",qry+i);
	dc(1);
	for(i=1;i<=q;i++)
		if(qry[i]) puts(ans[i]?"Yes":"No");
		else puts("Yes");
	return 0;
}
/*
6 5 
1 2 5 
1 3 7 
1 4 1 
3 5 2 
3 6 3 
1
8 
13 
14 
0
*/

