#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long ll;

const ll INF=1ll<<60;
const int MAXN=45,MAXV=2010,MAXE=1001000;

int N,M,S,T;

struct E{int next,to;ll cap;} e[MAXE];int ecnt,G[MAXV];
void addEdge(int u,int v,ll c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}
int dfn[MAXV];
std::queue<int> que;
bool calDfn()
{
	int i;
	memset(dfn,-1,sizeof(dfn));
	dfn[S]=0;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(e[i].cap<=0||dfn[v]>=0) continue;
			dfn[v]=dfn[u]+1;
			que.push(v);
		}
	}
	return dfn[T]>-1;
}
int iter[MAXV];
ll calF(int u,ll f)
{
	if(u==T) return f;
	for(int &i=iter[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(e[i].cap<=0||dfn[v]!=dfn[u]+1) continue;
		ll res=calF(v,std::min(f,e[i].cap));
		if(res>0)
		{
			e[i].cap-=res,e[i^1].cap+=res;
			return res;
		}
	}
	return 0;
}

ll maxFlow()
{
	int i;ll rFlow,res=0;
	while(calDfn())
	{
		for(i=1;i<=T;i++) iter[i]=G[i];
		while((rFlow=calF(S,INF))>0)
			res+=rFlow;
	}
	return res;
}

int mp[MAXN][MAXN];

int clr[MAXN][MAXN],id[MAXN][MAXN],idcnt;

inline bool jud(int r,int c)
{return r>=1&&r<=N&&c>=1&&c<=M;}
bool check(ll x)
{
	int i,j;
	ll flowSum=0;
	ecnt=1;memset(G,0,sizeof(G));
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			if(clr[i][j])
			{
				addEdge(S,id[i][j],x-mp[i][j]);
				flowSum+=x-mp[i][j];
				if(jud(i-1,j)) addEdge(id[i][j],id[i-1][j],INF);
				if(jud(i+1,j)) addEdge(id[i][j],id[i+1][j],INF);
				if(jud(i,j-1)) addEdge(id[i][j],id[i][j-1],INF);
				if(jud(i,j+1)) addEdge(id[i][j],id[i][j+1],INF);
			}
			else addEdge(id[i][j],T,x-mp[i][j]);
	return flowSum==maxFlow();
}
ll wN,wS,bN,bS;
inline void solve()
{
	int i,j;
	S=N*M+1,T=N*M+2;
	wN=wS=bN=bS=0;idcnt=0;
	int xMx=0;
	for(i=1;i<=N;i++) for(j=1;j<=M;j++)
		clr[i][j]=(i+j)&1,id[i][j]=++idcnt,xMx=std::max(xMx,mp[i][j]);
	for(i=1;i<=N;i++) for(j=1;j<=M;j++)
		if(clr[i][j]) wN++,wS+=mp[i][j];
		else bN++,bS+=mp[i][j];
	if(wN==bN&&wS!=bS) {puts("-1");return;}
	if(wN==bN)
	{
		ll l=xMx,r=(1LL<<50);
		while(l<=r)
		{
			ll mid=(l+r)>>1;
			if(check(mid)) r=mid-1;
			else l=mid+1;
		}
		printf("%lld\n",l*wN-wS);
	}
	else
	{
		ll x=(bS-wS)/(bN-wN);
		if(x<xMx) {puts("-1");return;}
		if(check(x)) printf("%lld\n",x*wN-wS);
		else puts("-1");
	}
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i,j;
		scanf("%d%d",&N,&M);
		for(i=1;i<=N;i++)
			for(j=1;j<=M;j++)
				scanf("%d",&mp[i][j]);
		solve();
	}
	return 0;
}
