#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=100,MAXM=10000;
int head[MAXN+1],ecnt;
struct node{int to,next;} e[MAXM+1];
void add(int x,int y){++ecnt,e[ecnt].to=y,e[ecnt].next=head[x],head[x]=ecnt;}

int dfn[MAXN+1],low[MAXN+1];
int times;

int root,ans;
int N;

void tarjan(int u)
{
	low[u]=dfn[u]=++times;
	for(int tmp=head[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(!dfn[v])
		{
			tarjan(v);
			low[u]=min(low[u],low[v]);
			if(u==1&&)
		}else low[u]=min(low[u],dfn[v]);
	}	
}
int main()
{
	while(scanf("%d",&N)&&N)
	{	
		int u,v;
		while(scanf("%d",&u)&&u)
			while(getchar()!='\n')
			{
				scanf("%d",&v);
				add(u,v);
				add(v,u);
			}
		tarjan(1);
	}
	return 0;
}
