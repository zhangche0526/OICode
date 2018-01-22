#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}

const int MAXN=1e3,MAXM=1e4,INF=1061109567;

int S,T;

struct E{int next,to,cap;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int c)
{
	e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
	e[++ecnt]=(E){G[v],u,c};G[v]=ecnt;
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

int N,M,Q;

int mnct[MAXN][MAXN];
int seq[MAXN],tmp[MAXN];
int rsp[MAXN*MAXN],rcnt;

bool inS[MAXN];
void bfs()
{
	inS[S]=true;que.push(S);
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
		{
			int v=e[i].to;
			if(inS[v]) continue;
			inS[v]=true,que.push(v);
		}
	}
}

void dc(int l,int r)
{
	if(l==r) return;
	
	int i,j,p1=l,p2=r;S=seq[l],T=seq[r];
	for(i=2;i<=ecnt;i+=2) e[i].cap=e[i^1].cap=(e[i].cap+e[i^1].cap)>>1;
	
	int mxF=maxFlow();
	
	memset(inS,false,sizeof inS);
	bfs();
	
	for(i=1;i<=N;i++) if(inS[i])
		for(j=1;j<=N;j++) if(!inS[j])
			umn(mnct[i][j],mxF),umn(mnct[j][i],mxF);

	for(i=l;i<=r;i++)
		if(inS[seq[i]]) tmp[p1++]=seq[i];
		else tmp[p2--]=seq[i];
	for(i=l;i<=r;i++) seq[i]=tmp[i];
	
	dc(l,p2);dc(p1,r);
}

int main()
{
	ecnt=1,memset(G,0,sizeof G);
	memset(mnct,0x3f,sizeof mnct);

	int i,j;scanf("%d%d",&N,&M);

	for(i=1;i<=N;i++) seq[i]=i;
	for(i=1;i<=M;i++)
	{
		int u,v,c;scanf("%d%d%d",&u,&v,&c);
		addEdge(u,v,c);
	}

	dc(1,N);

	rcnt=0;
	for(i=1;i<N;i++) for(j=i+1;j<=N;j++)
		rsp[++rcnt]=mnct[i][j];
	std::sort(rsp+1,rsp+rcnt+1);
	int ans=std::unique(rsp+1,rsp+rcnt+1)-rsp-1;
	printf("%d",ans);
	return 0;
}

/*
1
5 0
1
0
*/
