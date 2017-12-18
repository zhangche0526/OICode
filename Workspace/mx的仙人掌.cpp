#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<map>
#include<algorithm>
using std::min;
using std::max;
typedef long long ll;

const int MAXN=6e5+5;

int N,ncnt,M,Q,CNT;

ll A(int u,int v){return 1LL*u*MAXN+1LL*v;}
std::map<ll,ll> W[2];
struct E{int next,to;} e[MAXN<<3];int ecnt,G[2][MAXN];
void addEdge(int t,int u,int v,ll w=-1)
{
	if(u==v) return;
	if(~w)
	{
		if(W[t].count(A(u,v))) {W[t][A(u,v)]=min(W[t][A(u,v)],(ll)w);return;}
		W[t][A(u,v)]=w;
	}
	e[++ecnt]=(E){G[t][u],v};G[t][u]=ecnt;
}
void addEdge2(int t,int u,int v,ll w=-1){addEdge(t,u,v,w);addEdge(t,v,u,w);}

std::stack<int> st;
ll ringDis[MAXN],rLen[MAXN];
int dfn[MAXN],low[MAXN],dcnt;
void tarjan(int u,int la)
{
	st.push(u);
	dfn[u]=low[u]=++dcnt;
	for(int i=G[0][u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		if(!dfn[v])
		{
			ringDis[v]=ringDis[u]+W[0][A(u,v)];
			tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<=low[v])
			{
				rLen[++ncnt]=ringDis[st.top()]-ringDis[u]+W[0][A(u,st.top())];
				while(true)
				{
					int t=st.top();st.pop();
					addEdge(1,ncnt,t,min(ringDis[t]-ringDis[u],rLen[ncnt]-ringDis[t]+ringDis[u]));
					if(t==v) break;
				}
				addEdge(1,u,ncnt,0);
			}
		}else low[u]=min(low[u],dfn[v]);
	}
}

ll rtDis[MAXN];
int anc[MAXN][20];
int dpt[MAXN];
void dfs(int u)
{
	int i;dfn[u]=++dcnt;
	for(i=1;(1<<i)<=dpt[u];i++)
		anc[u][i]=anc[anc[u][i-1]][i-1];
	for(i=G[1][u];i;i=e[i].next)
	{
		int v=e[i].to;
		dpt[v]=dpt[u]+1;
		anc[v][0]=u;
		rtDis[v]=rtDis[u]+W[1][A(u,v)];
		dfs(v);
	}
}
void jmp(int &x,int tgt)
{
	for(int i=19;i>=0;i--)
		if(dpt[x]-(1<<i)>=tgt)
			x=anc[x][i];
}
inline int calLCA(int x,int y)
{
	int i;if(dpt[x]<dpt[y]) std::swap(x,y);
	jmp(x,dpt[y]);
	if(x==y) return x;
	for(i=19;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

int seq[MAXN],scnt;
bool cmp(int a,int b){return dfn[a]<dfn[b];}
void buildTree()
{
	int i;ecnt=0;
	std::sort(seq+1,seq+1+CNT,cmp);CNT=std::unique(seq+1,seq+CNT+1)-(seq+1);
	static int st[MAXN],tp;
	st[tp=1]=1;
	for(i=1;i<=CNT;i++)
	{
		int lca=calLCA(seq[i],st[tp]);
		while(dpt[st[tp-1]]>dpt[lca]) {addEdge(1,st[tp-1],st[tp]);tp--;}
		addEdge(1,lca,st[tp]);tp--;
		if(st[tp]!=lca) st[++tp]=lca;
		if(st[tp]!=seq[i]) st[++tp]=seq[i];
	}
	while(--tp) addEdge(1,st[tp],st[tp+1]);
}

ll ans,f[MAXN];
ll rF[MAXN<<1],rD[MAXN<<1];
int dq[MAXN];
inline void wrk(int r)
{
	int i,hd,tl;
	for(i=1;i<=scnt;i++) rF[i]=f[seq[i]],rD[i]=ringDis[seq[i]];
	rD[scnt+1]=rD[1]+rLen[r],rF[scnt+1]=rF[1];
	for(i=scnt+2;i<=scnt<<1;i++)
		rD[i]=rD[i-1]+rD[i-scnt]-rD[i-scnt-1],rF[i]=rF[i-scnt];
	dq[hd=tl=1]=1;
	for(i=2;i<=2*scnt;i++)
	{
		while(hd<=tl&&2*rD[i]>rLen[r]+2*rD[dq[hd]]) hd++;
		if(hd<=tl) ans=max(ans,rD[i]-rD[dq[hd]]+rF[i]+rF[dq[hd]]);
		while(hd<=tl&&rF[i]-rD[i]>=rF[dq[tl]]-rD[dq[tl]]) tl--;
		dq[++tl]=i;
	}
}

bool vis[MAXN];
void trDP(int u)
{
	int i;f[u]=0;
	if(u>N)
	{
		for(i=G[1][u];i;i=e[i].next)
			trDP(e[i].to);
		scnt=0;
		for(i=G[1][u];i;i=e[i].next)
		{
			int v=e[i].to;
			f[u]=max(f[u],f[v]+rtDis[v]-rtDis[u]);
			int x=v;jmp(x,dpt[u]+1);
			f[x]=f[v]+rtDis[v]-rtDis[x];
			seq[++scnt]=x;
		}
		std::reverse(seq+1,seq+1+scnt);
		wrk(u);
	}
	else
		for(i=G[1][u];i;i=e[i].next)
		{
			int v=e[i].to;
			trDP(v);
			if(vis[u]) ans=max(ans,f[u]+f[v]+rtDis[v]-rtDis[u]);
			f[u]=max(f[u],f[v]+rtDis[v]-rtDis[u]);
			vis[u]=true;
		}
	G[1][u]=0,vis[u]=false;
}

const int rt=1;
int main()
{
	int i;
	scanf("%d%d",&N,&M);ncnt=N;
	for(i=1;i<=M;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(0,u,v,w);
	}
	tarjan(rt,0);
	dcnt=0;
	dfs(rt);
	memset(G[1],0,sizeof G[1]);
	int Q;scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d",&CNT);
		for(i=1;i<=CNT;i++) scanf("%d",seq+i),vis[seq[i]]=true;
		buildTree();
		ans=0;
		trDP(rt);
		printf("%lld\n",ans);
	}
	return 0;
}
