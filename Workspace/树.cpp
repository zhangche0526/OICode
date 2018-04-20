#include<iostream>
#include<cstdio>
#include<cmath>
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
const int MAXN=1e5+5,INF=1061109567;

int n,q;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int anc[MAXN][20];
int dpt[MAXN],sz[MAXN];
int wpos[MAXN],wcnt;
void dfs(int u,int la)
{
	sz[u]=1,wpos[u]=++wcnt;
	for(int i=1;i<=log2(dpt[u]);i++)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dpt[v]=dpt[u]+1;
		anc[v][0]=u;
		dfs(v,u);
		sz[u]+=sz[v];
	}
}

const int rt=1;
struct SEGTN
{
	int l,r,lc,rc;
	int mx1,mxc,mx2,mn1,mnc,mn2,det;
} t[MAXN<<1];int tcnt=rt;
inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(lc.mx1>rc.mx1) t[o].mx1=lc.mx1,t[o].mxc=lc.mxc,t[o].mx2=max(lc.mx2,rc.mx1);
	else if(lc.mx1<rc.mx1) t[o].mx1=rc.mx1,t[o].mxc=rc.mxc,t[o].mx2=max(lc.mx1,rc.mx2);
	else t[o].mx1=lc.mx1,t[o].mxc=lc.mxc+rc.mxc,t[o].mx2=max(lc.mx2,rc.mx2);
	
	if(lc.mn1<rc.mn1) t[o].mn1=lc.mn1,t[o].mnc=lc.mnc,t[o].mn2=min(lc.mn2,rc.mn1);
	else if(lc.mn1>rc.mn1) t[o].mn1=rc.mn1,t[o].mnc=rc.mnc,t[o].mn2=min(lc.mn1,rc.mn2);
	else t[o].mn1=lc.mn1,t[o].mnc=lc.mnc+rc.mnc,t[o].mn2=min(lc.mn2,rc.mn2);
}
inline void execMx(int o,int v)
{
	t[o].mn1=v,umx(t[o].mx1,v);
	if(t[o].mx1==t[o].mn1)
	{
		t[o].mx2=-INF,t[o].mn2=INF;
		t[o].mxc=t[o].mnc=t[o].r-t[o].l+1;
	}else umx(t[o].mx2,v);
}
inline void execMn(int o,int v)
{
	t[o].mx1=v,umn(t[o].mn1,v);
	if(t[o].mx1==t[o].mn1)
	{
		t[o].mx2=-INF,t[o].mn2=INF;
		t[o].mxc=t[o].mnc=t[o].r-t[o].l+1;
	}else umn(t[o].mn2,v);
}
inline void psd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(lc.mx1>t[o].mx1) execMn(t[o].lc,t[o].mx1);
	if(rc.mx1>t[o].mx1) execMn(t[o].rc,t[o].mx1);
	if(lc.mn1<t[o].mn1) execMx(t[o].lc,t[o].mn1);
	if(rc.mn1<t[o].mn1) execMx(t[o].rc,t[o].mn1);
}

void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r)
	{
		t[o].mx1=t[o].mn1=0;
		t[o].mxc=t[o].mnc=1;
		t[o].mx2=-INF,t[o].mn2=INF;
		return;
	}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	upd(o);
}

void chMx(int o,int l,int r,int v)
{
	if(v<=t[o].mn1) return;
	if(l<=t[o].l&&t[o].r<=r)
		if(v<t[o].mn2) {execMx(o,v);return;}
	psd(o);
	int mid=t[o].l+t[o].r>>1;
	if(l<=mid) chMx(t[o].lc,l,r,v);
	if(r>mid) chMx(t[o].rc,l,r,v);
	upd(o);
}

int calMx(int o,int p)
{
	if(t[o].l==t[o].r) return t[o].mx1;
	psd(o);
	int mid=t[o].l+t[o].r>>1;
	if(p<=mid) return calMx(t[o].lc,p);
	return calMx(t[o].rc,p);
}

int jmp(int u,int k)
{
	for(int i=0;i<=log2(k);i++)
		if((k>>i)&1) u=anc[u][i];
	return u;
}

int main()
{
	int i;scanf("%d%d",&n,&q);
	for(i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	buildTree(rt,1,n);
	dfs(1,0);
	while(q--)
	{
		char opt[10];int x;scanf("%s%d",opt,&x);
		if(opt[0]=='C') chMx(rt,wpos[x],wpos[x]+sz[x]-1,dpt[x]);
		else printf("%d\n",jmp(x,dpt[x]-calMx(rt,wpos[x])));
	}
	return 0;
}
/*
7 1
1 2
2 3
3 4
4 5
4 6
6 7
Q 7
*/
