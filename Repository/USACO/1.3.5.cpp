/*
ID:zhangch33
TASK:wormhole
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int N;
struct P{int x,y;} pos[20];
int xnext[20],snext[20];
int head[20],hcnt;
int ans;

bool cmp(const P & a,const P & b)
{
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}

bool vis[20],inS[20];

void dfs(int x)
{
	int i;
	if(x==N)
	{
		bool needadd=false;
		for(i=1;i<=N;i++)
		{
			memset(inS,false,sizeof(inS));
			int rn=i;
			while(true)
			{
				 if(!xnext[rn]) break;
				 inS[rn]=true;
				 rn=snext[xnext[rn]];
				 if(inS[rn])
				 {
					 needadd=true;
					 break;
				 }
			}
			if(needadd)
			{
				ans++;
				break;
			}
		}			
	}
	else
	{
		if(!vis[x]) 
			for(i=1;i<=N;i++)
			{
				if(!vis[i]&&i!=x)
				{
					vis[i]=true,vis[x]=true;
					snext[x]=i,snext[i]=x;
					dfs(x+1);
					vis[i]=false,vis[x]=false;
				}
			}
		else  dfs(x+1);
	}
}
int main()
{
	freopen("wormhole.in","r",stdin);
	freopen("wormhole.out","w",stdout);
	int i;
	scanf("%d",&N);
	for(i=1;i<=N;i++) scanf("%d%d",&pos[i].x,&pos[i].y);
	sort(pos+1,pos+N+1,cmp);
	for(i=1;i<=N;i++)
	{
		if(pos[i+1].y!=pos[i].y) head[++hcnt]=i;
		else xnext[i]=i+1;
	}
	dfs(1);
	printf("%d\n",ans);
}
