#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}

const int MAXN=155,INF=1061109567;

int n,m;
int a[MAXN],wa[MAXN],b[MAXN],wb[MAXN];

const int MAXV=MAXN<<1,MAXE=MAXN*MAXN<<1;
int S,T;

struct E{int next,to,cap;} e[MAXE<<1];int ecnt,G[MAXV];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}

int dfn[MAXV];
std::queue<int> que;
bool calDfn(int u)
{
	memset(dfn,-1,sizeof dfn);
	dfn[S]=0;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
		{
			int v=e[i].to;
			if(~dfn[v]) continue;
			dfn[v]=dfn[u]+1;
			que.push(v);
		}
	}
	return ~dfn[T];
}

int iter[MAXV];
int calF(int u,int f)
{
	if(u==T) return f;
	for(int &i=iter[u];i;i=e[i].next) if(e[i].cap>0)
	{
		int v=e[i].to;
		if(dfn[v]!=dfn[u]+1) continue;
		int res=calF(v,min(f,e[i].cap));
		if(res>0)
		{
			e[i].cap-=res,e[i^1].cap+=res;
			return res;
		}
	}
	return 0;
}

int maxFlow()
{
	int f,res=0;
	while(calDfn(S))
	{
		memcpy(iter,G,sizeof G);
		while(f=calF(S,INF)) res+=f;
	}
	return res;
}

int f[MAXN],seq[MAXN];
inline int calc(int n,int *na,int *w)
{
	int i,j;
	ecnt=1;memset(G,0,sizeof G);
	memset(seq,0x3f,sizeof seq);
	for(i=1;i<=n;i++)
	{
		int p=std::lower_bound(seq+1,seq+n+1,na[i])-seq;
		f[i]=p;
		seq[p]=na[i];
	}
	int LIS=0;for(i=1;i<=n;i++) umx(LIS,f[i]);

	S=(n+1)<<1,T=(n+1)<<1|1;
	for(i=1;i<=n;i++)
	{
		addEdge(i<<1,i<<1|1,w[i]);
		if(f[i]==1) addEdge(S,i<<1,INF);
		if(f[i]==LIS) addEdge(i<<1|1,T,INF);
	}
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(na[i]<na[j]&&f[i]+1==f[j])
				addEdge(i<<1|1,j<<1,INF);
	return maxFlow(); 
}

int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	for(i=1;i<=n;i++) scanf("%d",wa+i);
	scanf("%d",&m);
	for(i=1;i<=m;i++) scanf("%d",b+i);
	for(i=1;i<=m;i++) scanf("%d",wb+i);
	printf("%d",min(calc(n,a,wa),calc(m,b,wb)));
	return 0;
}
/*
5
1 5 9 2 7
1 2 1 3 1
4
4 3 6 8
1 2 1 1
*/
