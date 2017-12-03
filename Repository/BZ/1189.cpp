#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

const int rm[4]={-1,1,0,0},cm[4]={0,0,-1,1};
const int MAXN=25,MAXT=405,MAXV=2e5+5,MAXE=1e6+5;

int N,M;

int mp[MAXN][MAXN],dis[MAXN][MAXN],ndT[MAXN][MAXN];

struct P{int r,c;P(int r=0,int c=0):r(r),c(c){};};
P door[MAXN][MAXN];
std::queue<P> que;
bool vis[MAXN][MAXN];
int bfs(int r,int c)
{
	while(!que.empty()) que.pop();
	memset(dis,0,sizeof(dis));
	memset(vis,false,sizeof(vis));
	que.push(P(r,c));dis[r][c]=0,vis[r][c]=true;
	while(!que.empty())
	{
		P u=que.front();que.pop();
		if(vis[u.r][u.c]) continue;
		vis[u.r][u.c]=true;
		for(int i=0;i<4;i++)
		{
			P v=P(u.r+rm[i],u.c+cm[i]);
			if(v.r<1||v.r>N||v.c<1||v.c>M) continue;
			dis[v.r][v.c]=dis[u.r][u.c]+1;
			if(mp[v.r][v.c]==2)
			{
				door[r][c]=v;
				return dis[v.r][v.c];
			}
			que.push(v);
		}
	}
	return 0;
}

int S,T;
int Pid[MAXN][MAXN],idcnt;
int Did[MAXN][MAXN][MAXT];
bool check(int x)
{
	ecnt=1;memset(G,0,sizeof(G));idcnt=0;
	int i,j,k;
	for(i=1;i<=N;i++) for(j=1;j<=M;j++)
		if(mp[i][j]==1) Pid[i][j]=++idcnt;
	for(i=1;i<=N;i++) for(j=1;j<=M;j++)
		if(mp[i][j]==2) for(k=1;k<=x;k++) 
			Did[i][j][k]=++idcnt;
	S=++idcnt,T=++idcnt;

	int flowSum=0;
	for(i=1;i<=N;i++) for(j=1;j<=M;j++)
		if(mp[i][j]==1)
		{
			addEdge(S,Pid[i][j],1);flowSum++;
			addEdge(Pid[i][j],Did[door[i][j].r][door[i][j].c][ndT[i][j]]);
		}
	for(i=1;i<=N;i++) for(j=1;j<=M;j++)
		if(mp[i][j]==2) for(k=1;k<=x;k++)
		{
			addEdege(Did[i][j][k],T,1);
			if(k>1) addEdge(Did[i][j][k-1],Did[i][j][k],1);
		}
	return flowSum==dinic();
}

int main()
{
	int i,j;char c;
	scanf("%d%d",&N,&M);
	for(i=1;i<=N:i++)
		for(j=1;j<=M;j++)
		{
			do c=getchar();while(c!='.'&&c!='X'&&c!='D');
			if(c=='.') mp[i][j]=1;
			else if(c=='D') mp[i][j]=2;
		}
	int tmp;
	for(i=1;i<=N;i++)
		for(j=1;j=M;j++)
			if(mp[i][j]==1)
			{
				if(tmp=bfs(i,j)) ndT[i][j]=tmp;
				else {puts("impossible");return 0;}
			}
	
	return 0;
}
