#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using std::min;

const int MAXN=25,MAXV=2e3+5,MAXE=2e4+5,INF=1061109567;

int S,T;

struct E{int next,to,cap;} e[MAXE<<1];int ecnt=1,G[MAXV];
inline void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
}

int dpt[MAXV];
std::queue<int> que;
bool calDpt()
{
	memset(dpt,-1,sizeof dpt);
	dpt[S]=0;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(e[i].cap)
		{
			int v=e[i].to;if(~dpt[v]) continue;
			dpt[v]=dpt[u]+1;
			que.push(v);
		}
	}
	return ~dpt[T];
}

int iter[MAXV];
int calF(int u,int f)
{
	if(u==T) return f;
	for(int &i=iter[u];i;i=e[i].next) if(e[i].cap)	
	{
		int v=e[i].to;if(dpt[v]!=dpt[u]+1) continue;
		int res=calF(v,min(e[i].cap,f));
		if(res)
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

int R,C,d;
inline int id(int r,int c){return (r-1)*C+c;}

int H[MAXN][MAXN];
bool mp[MAXN][MAXN];

inline void buildGraph()
{
	int i,j;S=id(R,C)+1<<1,T=S|1;
	for(i=1;i<=R;i++) for(j=1;j<=C;j++) if(mp[i][j]) addEdge(S,id(i,j)<<1,1);
	for(i=1;i<=R;i++) for(j=1;j<=C;j++) if(H[i][j]) addEdge(id(i,j)<<1,id(i,j)<<1|1,H[i][j]);
	for(int r=1;r<=R;r++) for(int c=1;c<=C;c++) if(H[r][c])
	{
		if(r-d<1||r+d>R||c-d<1||c+d>C) {addEdge(id(r,c)<<1|1,T,INF);continue;}
		for(i=-d;i<=d;i++) for(j=-d;j<=d;j++)
			if(abs(i)+abs(j)&&abs(i)+abs(j)<=d)
			{
				int nr=r+i,nc=c+j;
				if(nr<1||nr>R||nc<1||nc>C) continue;
				if(H[nr][nc]) addEdge(id(r,c)<<1|1,id(nr,nc)<<1,INF);
			}
	}
}

int main()
{
	static char s[MAXN];
	int i,j;scanf("%d%d%d",&R,&C,&d);
	for(i=1;i<=R;i++)
	{
		scanf("%s",s);
		for(j=1;j<=C;j++) H[i][j]=s[j-1]-'0';
	}
	int ans=0;
	for(i=1;i<=R;i++)
	{
		scanf("%s",s);
		for(j=1;j<=C;j++) ans+=mp[i][j]=s[j-1]=='L';
	}
	buildGraph();
	ans-=maxFlow();
	printf("%d",ans);
	return 0;
}
