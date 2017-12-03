#include<iostream>
#include<cstdio>
#include<cstring>
#include<stack>
#include<vector>

const int MAXN=1e3+5,MAXM=1e6+5;

int n,m;

bool ban[MAXN][MAXN];
struct E{int next,fr,to;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],u,v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

std::vector<int> bcc[MAXN];int bcnt,belong[MAXN];

std::stack<E> st;
int low[MAXN],dfn[MAXN],dcnt;
void tarjan(int u,int la)
{
	low[u]=dfn[u]=++dcnt;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			st.push((E){0,u,v});
			tarjan(v,u);
			low[u]=std::min(low[u],low[v]);
			if(low[v]>=dfn[u])
			{
				bcc[++bcnt].clear();
				E t;
				do
				{
					t=st.top();st.pop();
					if(belong[t.fr]!=bcnt) bcc[bcnt].push_back(t.fr),belong[t.fr]=bcnt;
					if(belong[t.to]!=bcnt) bcc[bcnt].push_back(t.to),belong[t.to]=bcnt;
				}while(t.fr!=u||t.to!=v);
			}
		}else if(dfn[v]<dfn[u]&&v!=la)
		{
			st.push((E){0,u,v});
			low[u]=std::min(low[u],dfn[v]);
		}
	}
}

inline void findBCC()
{
	memset(dfn,0,sizeof(dfn));
	memset(belong,0,sizeof(belong));
	dcnt=bcnt=0;
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i,0);
}

int clr[MAXN];

bool judBi(int u,int bid)
{
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(belong[v]!=bid) continue;
		if(clr[u]==clr[v]) return false;
		if(clr[v]==-1)
		{
			clr[v]=clr[u]^1;
			if(!judBi(v,bid)) return false;
		}
	}
	return true;
}

bool inOddRing[MAXN];
inline void calOdd()
{
	int i,j;
	memset(inOddRing,false,sizeof(inOddRing));
	for(i=1;i<=bcnt;i++)
	{
		memset(clr,-1,sizeof(clr));
		for(j=0;j<bcc[i].size();j++) belong[bcc[i][j]]=i;
		clr[bcc[i][0]]=0;
		if(!judBi(bcc[i][0],i))
			for(j=0;j<bcc[i].size();j++) inOddRing[bcc[i][j]]=true;
	}
}

int main()
{
	int Case=0;
	while(~scanf("%d%d",&n,&m)&&(n||m))
	{
		memset(ban,false,sizeof(ban));
		memset(G,0,sizeof(G));ecnt=0;
		int i,j;
		for(i=1;i<=m;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			ban[u][v]=ban[v][u]=true;
		}
		for(i=1;i<n;i++)
			for(j=i+1;j<=n;j++)
				if(!ban[i][j]) addEdge2(i,j);
		findBCC();
		calOdd();
		int ans=0;
		for(i=1;i<=n;i++) if(!inOddRing[i]) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
