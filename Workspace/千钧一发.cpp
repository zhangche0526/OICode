#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
#include<cmath>
using std::floor;
using std::min;
typedef long long ll;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
const int MAXN=1e3+100,MAXM=1e6+1e5,INF=1061109567;

int S,T;

struct E{int next,to,cap;} e[MAXM<<1];int ecnt=1,G[MAXN];
void addEdge(int u,int v,int c)
{	
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
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

int maxFlow()
{
	int f,res=0;
	while(calDpt())
	{
		memcpy(iter,G,sizeof G);
		while(f=calF(S,INF)) res+=f;
	}
	return res;
}


int n;
int A[MAXN],B[MAXN];
inline bool jud(int i,int j)
{
	double SAA=sqrt((ll)A[i]*A[i]+(ll)A[j]*A[j]);
	if(floor(SAA)!=SAA) return true;
	if(gcd(A[i],A[j])>1) return true;
	return false;
}
inline void buildGraph()
{
	int i,j;S=n+1,T=n+2;
	for(i=1;i<=n;i++)
		if(A[i]&1) addEdge(S,i,B[i]);
		else addEdge(i,T,B[i]);
	for(i=1;i<=n;i++) if(A[i]&1)
		for(j=1;j<=n;j++) if(!(A[j]&1))
			if(!jud(i,j)) addEdge(i,j,INF);
}
int main()
{
	int i,ans=0;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",A+i);
	for(i=1;i<=n;i++) scanf("%d",B+i),ans+=B[i];
	buildGraph();
	ans-=maxFlow();
	printf("%d",ans);
	return 0;
}
