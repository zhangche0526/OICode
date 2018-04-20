#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
template<typename Ty>
inline void umn(Ty &a,Ty b){a=min(a,b);}
using std::max;
template<typename Ty>
inline void umx(Ty &a,Ty b){a=max(a,b);}
typedef long long ll;

const int MAXN=3e5+5;
const ll INF=1e18;

int n,K;

struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}

struct F{ll res;int k;F(ll res,int k):k(k),res(res){} F(){} } f[MAXN][3];
bool operator <(const F &a,const F &b){return a.res<b.res||(a.res==b.res&&a.k<b.k);}
bool operator >(const F &a,const F &b){return a.res>b.res||(a.res==b.res&&a.k>b.k);}
F operator +(const F &a,const F &b){return F(a.res+b.res,a.k+b.k);}

int dfnseq[MAXN],dcnt;
int dpt[MAXN],mxd;

int fa[MAXN];
void predfs(int u)
{
	dfnseq[++dcnt]=u;
	umx(mxd,dpt[u]);
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==fa[u]) continue;
		dpt[v]=dpt[u]+1;
		fa[v]=u;
		predfs(v);
	}
}

F ans;
void dfs(ll V)
{
	for(int i=dcnt;i;i--)
	{
		int u=dfnseq[i];
		f[u][0]=F(-V,1);
		f[u][1]=F(-INF,0);
		f[u][2]=F(0,0);	
		for(int j=G[u];j;j=e[j].next)
		{
			int v=e[j].to;if(v==fa[u]) continue;
			static F tmp[3];memcpy(tmp,f[u],sizeof f[u]);
			for(int a=2;~a;a--) for(int b=2;~b;b--)
			{
				umx(f[u][a],tmp[a]+f[v][b]);
				if(a<2&&b<2) umx(f[u][a+1],tmp[a]+f[v][b]+F(V+e[j].val,-1));
			}
		}
	}
	ans=f[1][0];for(int i=1;i<=2;i++) umx(ans,f[1][i]);
}

int main()
{
	freopen("lct.in","r",stdin);
	freopen("lct.out","w",stdout);
	int i;scanf("%d%d",&n,&K);K++;
	ll l=0,r=0;
	for(i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);
		r+=max(0,w);umn(l,(ll)-w);
	}
	predfs(1);
	while(l<=r)
	{
		ll mid=l+r>>1;
		dfs(mid);
		if(ans.k<K) r=mid-1;
		else l=mid+1;
	}
	dfs(r);
	printf("%lld",ans.res+(ll)K*r);
	return 0;
}
/*
5 1
1 2 3
2 3 5
2 4 -3
4 5 6
*/
