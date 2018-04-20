#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int MAXN=1e5+5;

int n,m;

int fa[MAXN];
struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int V[MAXN];
int val[MAXN],blg[MAXN],gcnt;
inline void dcrt()
{
	memcpy(val,V,sizeof V);std::sort(val+1,val+n+1);
	gcnt=std::unique(val+1,val+n+1)-(val+1);
	for(int i=1;i<=n;i++) blg[i]=std::lower_bound(val+1,val+gcnt+1,V[i])-val;
}

struct CMT{int lc,rc,sz;} t[MAXN*40];int tcnt,rt[MAXN];
void ist(int &o,int la,int l,int r,int p)
{
	t[o=++tcnt]=t[la];
	t[o].sz++;
	if(l==r) return;
	int mid=l+r>>1;
	if(p<=mid) ist(t[o].lc,t[la].lc,l,mid,p);
	else ist(t[o].rc,t[la].rc,mid+1,r,p);
}
inline void ist(int x,int v){ist(rt[x],rt[fa[x]],1,gcnt,v);}
int findK(int a,int b,int c,int d,int l,int r,int k)
{
	if(l==r) return val[l];
	int lsz=t[t[a].lc].sz+t[t[b].lc].sz-t[t[c].lc].sz-t[t[d].lc].sz;
	int mid=l+r>>1;
	if(k<=lsz) return findK(t[a].lc,t[b].lc,t[c].lc,t[d].lc,l,mid,k);
	return findK(t[a].rc,t[b].rc,t[c].rc,t[d].rc,mid+1,r,k-lsz);
}
inline int findK(int x,int y,int l,int k){return findK(rt[x],rt[y],rt[l],rt[fa[l]],1,gcnt,k);}

int dpt[MAXN];
int wpos[MAXN],wseq[MAXN<<1],wcnt;
void predfs(int u,int la)	
{
	wseq[wpos[u]=++wcnt]=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dpt[v]=dpt[u]+1;
		predfs(v,u);
		wseq[++wcnt]=u;
	}
}
int st[MAXN<<1][20];
inline void initLCA()
{
	int i,k;predfs(1,0);
	for(i=1;i<=n<<1;i++) st[i][0]=wseq[i];
	for(k=1;k<=log2(n<<1);k++)
		for(i=1;i+(1<<k)-1<=n<<1;i++)
			st[i][k]=dpt[st[i][k-1]]<dpt[st[i+(1<<k-1)][k-1]]?st[i][k-1]:st[i+(1<<k-1)][k-1];
}
int cLCA(int x,int y)
{
	int l=wpos[x],r=wpos[y];
	if(l>r) std::swap(l,r);
	int k=log2(r-l+1);
	return dpt[st[l][k]]<dpt[st[r-(1<<k)+1][k]]?st[l][k]:st[r-(1<<k)+1][k];
}

inline int qry(int x,int y,int k){return findK(x,y,cLCA(x,y),k);}

void dfs(int u,int la)
{
	ist(u,blg[u]);
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		fa[v]=u;
		dfs(v,u);
	}
}

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",V+i);
	dcrt();
	for(i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	dfs(1,0);
	initLCA();
	int ans=0;
	while(m--)
	{
		int x,y,k;scanf("%d%d%d",&x,&y,&k);x^=ans;
		printf("%d\n",ans=qry(x,y,k));
	}
	return 0;
}
/*
8 1
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 2
*/
