#include<iostream>
#include<cstdio>
#include<cmath>
using std::log2;
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
inline double sqr(double x){return x*x;}

const int MAXN=1e5+5;
const double eps=1e-10;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int dseq[MAXN<<1],wpos[MAXN],wcnt;
int dpt[MAXN];
void dfs(int u,int la)
{
	dseq[wpos[u]=++wcnt]=dpt[u];
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dpt[v]=dpt[u]+1;
		dfs(v,u);
		dseq[++wcnt]=dpt[u];
	}
}
int st[MAXN<<1][20];
void initST(int n)
{
	for(int i=1;i<=n;i++) st[i][0]=dseq[i];
	for(int k=1;k<=log2(n);k++)
		for(int i=1;i+(1<<k)-1<=n;i++)
			st[i][k]=min(st[i][k-1],st[i+(1<<k-1)][k-1]);
}
int calMn(int l,int r)
{
	if(l>r) std::swap(l,r);
	int k=log2(r-l+1);
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
inline int dis(int x,int y){return dpt[x]+dpt[y]-2*calMn(wpos[x],wpos[y]);}

bool vis[MAXN];
int sz,mxv[MAXN],mnv,rt;
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
void calRt(int u,int la,int r)
{
	umx(mxv[u],sz[r]-sz[u]);
	if(mxv[u]<mnv) mnv=mxv[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calRt(v,u);
	}
}
int fa[MAXN];
void treeDC(int u)
{
	mnv=n;calSz(u,0);calRt(u,0,u);
	vis[rt]=true;
	for(int i=G[rt];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		fa[v]=rt;
		treeDC(v);
	}
}

double P[MAXN];
struct S{double A1,A2,B1,B2,B3;} plus[MAXN],minus[MAXN];

void mdf(int x,double p)
{
	double det=p-P[x];
	plus[x].A2+=det,plus[x].B3+=P[x]*(1.0-P[x]);
	for(int u=x;fa[u];u=fa[u])
	{
		int d=dis(x,fa[u]);

		plus[fa[u]].A1+=d*P[x];
		plus[fa[u]].A2+=P[x];
		plus[fa[u]].B1+=sqr(d)*P[x]*(1.0-P[x]);
		plus[fa[u]].B2+=2*d*P[x]*(1.0-P[x]);
		plus[fa[u]].B3+=P[x]*(1.0-P[x]);

		minus[u].A1+=d*P[x];
		minus[u].A2+=P[x];
		minus[u].B1+=sqr(d)*P[x]*(1.0-P[x]);
		minus[u].B2+=2*d*P[x]*(1.0-P[x]);
		minus[u].B3+=P[x]*(1.0-P[x]);
	}
	P[x]=p;
}

double 

int main()
{
	int i;

	return 0;
}
