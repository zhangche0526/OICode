/*
TASK:castle
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int MAXM=50,MAXN=50;
const int m[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
int M,N;
int mat[MAXN+1][MAXM+1];
struct node{int r,c;};

int roomId[MAXN+1][MAXM+1],rcnt,roomSize[MAXM*MAXN+1];

struct W{int r,c;char d;int v;} wall[2*MAXM*MAXN+1];int wcnt;
bool cmp(const W & a,const W & b)
{
	if(a.v==b.v)
	{
		if(a.c==b.c) return a.r>b.r;
		return a.c<b.c;
	}
	return a.v>b.v;
}

bool vis[MAXN+1][MAXM+1];
void findRoom(node s,int id)
{
	int i,j;
	queue<node> que;
	vis[s.r][s.c]=true;
	que.push(s);
	while(!que.empty())
	{
		node u=que.front();que.pop();
		++roomSize[id];
		roomId[u.r][u.c]=id;
		int w=mat[u.r][u.c];
		for(i=1,j=0;j<4;i<<=1,++j)
		{
			node v=(node){u.r+m[j][0],u.c+m[j][1]};
			if(!vis[v.r][v.c])
				if(!(i&w)) 
				{
					que.push(v);
					vis[v.r][v.c]=true;
				}
		}
	}
}

void findWall()
{
	int i,j;
	queue<node> que;
	memset(vis,false,sizeof(vis));
	que.push((node){1,1});
	vis[1][1]=true;
	while(!que.empty())
	{
		node u=que.front();que.pop();
		for(i=0;i<4;i++)
		{
			node v=(node){u.r+m[i][0],u.c+m[i][1]};
			if(v.r>=1&&v.r<=N&&v.c>=1&&v.c<=M)
				{
					if(i==1||i==2)
						if(roomId[u.r][u.c]!=roomId[v.r][v.c])
							wall[++wcnt]=(W){u.r,u.c,i==1?'N':'E',roomSize[roomId[u.r][u.c]]+roomSize[roomId[v.r][v.c]]};
					if(!vis[v.r][v.c])
					{ 
						que.push(v);
						vis[v.r][v.c]=true;
					}
				}
		}
	}
}

int main()
{
	freopen("castle.in","r",stdin);
	freopen("castle.out","w",stdout);
	int i,j;
	///read
	scanf("%d%d",&M,&N);
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			scanf("%d",&mat[i][j]);
	///1
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
			if(!vis[i][j])
				findRoom((node){i,j},++rcnt);
	printf("%d\n",rcnt);
	///2
	int maxRS=0;
	for(i=1;i<=rcnt;i++)
		if(roomSize[i]>maxRS) maxRS=roomSize[i];
	printf("%d\n",maxRS);
	///3&4
	findWall();
	sort(wall+1,wall+wcnt+1,cmp);
	printf("%d\n%d %d %c\n",wall[1].v,wall[1].r,wall[1].c,wall[1].d);
	///
}
