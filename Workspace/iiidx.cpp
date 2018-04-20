#include<iostream>
#include<cstdio>
#include<algorithm>

const int MAXN=5e5+5;

int n;double k;
int a[MAXN],id[MAXN],ans[MAXN];

int sz[MAXN];
struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}

int sum[MAXN<<2];
void ptAdd(int o,int lp,int rp,int p,int v)
{
	sum[o]+=v;
	if(lp==rp) return;
	int mid=lp+rp>>1;
	if(p<=mid) ptAdd(o<<1,lp,mid,p,v);
	else ptAdd(o<<1|1,mid+1,rp,p,v);
}
int findK(int o,int lp,int rp,int k)
{
	if(lp==rp) return lp;
	int mid=lp+rp>>1;
	if(k<=sum[o<<1|1]) return findK(o<<1|1,mid+1,rp,k);
	return findK(o<<1,lp,mid,k-sum[o<<1|1]);
}
inline void mdf(int p,int v){ptAdd(1,1,n,p,v);}
inline int qry(int k){return findK(1,1,n,k);}

int main()
{
	freopen("iiidx.in","r",stdin);
	freopen("iiidx.out","w",stdout);
	int i,j;scanf("%d%lf",&n,&k);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	std::sort(a+1,a+n+1);
	for(i=n;i;i--) id[i]=a[i]==a[i+1]?id[i+1]+1:1;
	for(i=n;i;i--)
	{
		int fa=(double)i/k;
		addEdge(fa,i);sz[fa]+=++sz[i];
	}
	for(int v=e[i=G[0]].to;i;v=e[i=e[i].next].to)
		mdf(v,sz[v]);
	for(i=1;i<=n;i++)
	{
		int u=qry(id[i]);
		ans[u]=a[i];
		mdf(u,-sz[u]);
		for(int v=e[j=G[u]].to;j;v=e[j=e[j].next].to)
			mdf(v,sz[v]);
	}
	for(i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
/*
10 2
1 2 2 3 3 3 4 4 4 4
*/
