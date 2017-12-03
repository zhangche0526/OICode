#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int T;
const int MAXRC=1000,mov[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
bool maze[MAXRC+1][MAXRC+1];
int fire[MAXRC+1][MAXRC+1];
int R,C;
struct node{int pos[2],t;};

bool vis[MAXRC+1][MAXRC+1];

queue<node> bfsque;

queue<node> fque;
inline void initFire()
{
	while(!fque.empty()) fque.pop();
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
			if(fire[i][j]==0)
			{
				node x;
				x.pos[0]=i,x.pos[1]=j;
				fque.push(x);
			}

	while(!fque.empty())
	{
		node u=fque.front();fque.pop();
		for(int i=0;i<4;i++)
		{
			node v;
			for(int j=0;j<2;j++) v.pos[j]=u.pos[j]+mov[i][j];
			if(v.pos[0]>=1&&v.pos[0]<=R&&v.pos[1]>=1&&v.pos[1]<=C)
				if((!maze[v.pos[0]][v.pos[1]])&&(fire[v.pos[0]][v.pos[1]]==-1))
					if(!vis[v.pos[0]][v.pos[1]])
					{
						fire[v.pos[0]][v.pos[1]]=fire[u.pos[0]][u.pos[1]]+1;
						fque.push(v);
						vis[v.pos[0]][v.pos[1]]=true;
					}
		}
	}
}
int main()
{
	//freopen("11624.in","r",stdin);
	//freopen("11624.out","w",stdout);
	cin>>T;
	while(T--)
	{
		//Init
		scanf("%d%d",&R,&C);
		memset(maze,false,sizeof(maze));
		memset(fire,-1,sizeof(maze));
		int i,j;
		node J;
		//
		//read
		for(i=1;i<=R;i++)
			for(j=1;j<=C;j++)
			{
				char x;
				do x=getchar();
				while(x!='#'&&x!='.'&&x!='J'&&x!='F');
				if(x=='#') maze[i][j]=true;
				if(x=='F') fire[i][j]=0;
				if(x=='J') J.pos[0]=i,J.pos[1]=j;
			}
		//
		initFire();
		//bfs
		while(!bfsque.empty()) bfsque.pop();
		J.t=0;
		bfsque.push(J);
		memset(vis,false,sizeof(vis));
		bool found=false;
		int ans;
		while(!bfsque.empty())
		{
			node u=bfsque.front();bfsque.pop();
			if(u.pos[0]==1||u.pos[0]==R||u.pos[1]==1||u.pos[1]==C)
			{
				ans=u.t+1,found=true;
				break;
			}
			for(int i=0;i<4;i++)
			{
				node v;
				v.t=u.t+1;
				for(int j=0;j<2;j++) v.pos[j]=u.pos[j]+mov[i][j];
				if(v.pos[0]>=1&&v.pos[0]<=R&&v.pos[1]>=1&&v.pos[1]<=C)
					if((!maze[v.pos[0]][v.pos[1]])&&(v.t<fire[v.pos[0]][v.pos[1]]||fire[v.pos[0]][v.pos[1]]==-1))
						if(!vis[v.pos[0]][v.pos[1]])
						{
							bfsque.push(v);
							vis[v.pos[0]][v.pos[1]]=true;
						}
			}
		}
		//
		//print
		if(found) printf("%d\n",ans);
		else printf("IMPOSSIBLE\n");
		//
	}
	return 0;
}
