#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<cstring>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}

const int MAXN=4e3+5,MAXM=6e4+5,INF=1061109567;

int N,M,S,T;

struct E{int next,fr,to,cap;} e[MAXM<<1];int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],u,v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],v,u,0};G[v]=ecnt;
}

std::queue<int> que;
int dpt[MAXN];
bool calDpt()
{
	memset(dpt,-1,sizeof dpt);
	que.push(S);dpt[S]=0;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
		{
			int v=e[i].to;
			if(~dpt[v]) continue;
			dpt[v]=dpt[u]+1;
			que.push(v);
		}
	}
	return ~dpt[T];
}

int iter[MAXN];
int calF(int u,int f)
{
	if(u==T) return f;
	for(int &i=iter[u];i;i=e[i].next) if(e[i].cap>0)
	{
		int v=e[i].to;
		if(dpt[v]!=dpt[u]+1) continue;
		int res=calF(v,min(f,e[i].cap));
		if(res>0)
		{
			e[i].cap-=res,e[i^1].cap+=res;
			return res;
		}
	}
	return 0;
}

void maxFlow()
{
	int f;
	while(calDpt())
	{
		memcpy(iter,G,sizeof G);
		while(f=calF(S,INF));
	}
}

int dfn[MAXN],dcnt,low[MAXN];
std::stack<int> st;bool inSt[MAXN];
int gr[MAXN],gcnt;
void tarjan(int u)
{
	dfn[u]=low[u]=++dcnt;
	st.push(u);inSt[u]=true;
	for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
	{
		int v=e[i].to;
		if(!dfn[v])
		{
			tarjan(v);
			umn(low[u],low[v]);
		}else if(inSt[v]) umn(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		int t;gcnt++;
		do
		{
			t=st.top();st.pop();
			inSt[t]=false;
			gr[t]=gcnt;
		}while(t!=u);
	}
}

int main()
{
	int i;
	scanf("%d%d%d%d",&N,&M,&S,&T);
	for(i=1;i<=M;i++)
	{
		int u,v,c;scanf("%d%d%d",&u,&v,&c);
		addEdge(u,v,c);
	}
	maxFlow();
	for(i=1;i<=N;i++) if(!dfn[i]) tarjan(i);
	for(i=2;i<=ecnt;i+=2)
		if(!e[i].cap&&gr[e[i].fr]!=gr[e[i].to])
		{
			if(gr[e[i].fr]==gr[S]&&gr[e[i].to]==gr[T])
				puts("1 1");
			else puts("1 0");
		}else puts("0 0");
	return 0;
}
