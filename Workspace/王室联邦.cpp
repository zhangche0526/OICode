#include<iostream>
#include<cstdio>

const int MAXN=1005;

int N,B;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

int root[MAXN],rcnt,blg[MAXN];
int st[MAXN],tp;

void dfs(int u,int la)
{
	int tmp=tp;
	for(int i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(v==la) continue;
		dfs(v,u);
		if(tp-tmp>=B) 
		{
			root[++rcnt]=u;
			while(tp>tmp) blg[st[tp--]]=rcnt;
		}
	}
	st[++tp]=u;
}

int main()
{
	int i;
	scanf("%d%d",&N,&B);
	for(i=1;i<N;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	dfs(1,0);
	while(tp) blg[st[tp--]]=rcnt;
	printf("%d\n",rcnt);
	for(i=1;i<=N;i++) printf("%d ",blg[i]);puts("");
	for(i=1;i<=rcnt;i++) printf("%d ",root[i]);
	return 0;
}
