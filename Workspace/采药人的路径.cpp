#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
using std::abs;
typedef long long ll;

const int MAXN=1e5+5;

int n;

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

void calRt(int u,int la,int r)
{
	umx(mxv[u],sz[r]-sz[u]);
	if(mxv[u]<mnv) mnv=mxv[u],rt=u;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		calRt(v,u,r);
	}
}

int mxDis;
int tmp[4][MAXN<<1];
int *C[2]={tmp[0]+MAXN,tmp[1]+MAXN},*c[2]={tmp[2]+MAXN,tmp[3]+MAXN};

void dfs(int u,int la,int d)
{
	static int tmp[MAXN<<1];
	static int *cnt=tmp+MAXN;
	umx(mxDis,abs(d));
	++c[bool(cnt[d])][d];
	++cnt[d];
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la||vis[v]) continue;
		dfs(v,u,d+e[i].val);
	}
	--cnt[d];
}

inline ll calc(int u)
{
	ll res=0;mxDis=0;
	C[0][0]=1;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		dfs(v,0,e[i].val);
		res+=(ll)c[0][0]*(C[0][0]-1);
		for(int s=-mxDis;s<=mxDis;s++)
			res+=(ll)c[1][s]*C[0][-s],
			res+=(ll)c[0][s]*C[1][-s],
			res+=(ll)c[1][s]*C[1][-s];
		for(int s=-mxDis;s<=mxDis;s++)
		{
			C[0][s]+=c[0][s];
			C[1][s]+=c[1][s];
		}
		for(int s=-mxDis;s<=mxDis;s++)
			c[0][s]=c[1][s]=0;
	}
	for(int s=-mxDis;s<=mxDis;s++)
		C[0][s]=C[1][s]=0;
	return res;
}

ll ans;
void treeDC(int u)
{
	mnv=n;calSz(u,0);calRt(u,0,u);
	vis[rt]=true;ans+=calc(rt);
	for(int i=G[rt];i;i=e[i].next)
	{
		int v=e[i].to;
		if(vis[v]) continue;
		treeDC(v);
	}
}

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		if(!w) w=-1;
		addEdge2(u,v,w);
	}
	treeDC(1);
	printf("%lld",ans);
	return 0;
}
