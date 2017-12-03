/**************************************************************
    Problem: 1006
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1108 ms
    Memory:29364 kb
****************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

const int MAXN=1e4+5,MAXM=1e6+5;

int n,m;
struct E{int next,to;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}

struct HN{int id,v;};
bool operator >(HN a,HN b){return a.v>b.v;}
bool operator <(HN a,HN b){return a.v<b.v;}
std::priority_queue<HN> heap;

int label[MAXN],mark[MAXN],seq[MAXN];

inline void MCS()
{
	int i,j;
	for(i=1;i<=n;i++) heap.push((HN){i,0});
	for(i=n;i>=1;)
	{
		int u=heap.top().id;heap.pop();
		if(mark[u]) continue;
		seq[i]=u,mark[u]=i--;
		for(j=G[u];j;j=e[j].next)
		{
			int v=e[j].to;
			if(mark[v]) continue;
			label[v]++;
			heap.push((HN){v,label[v]});
		}
	}
}

void color(int u)
{
	int i,j;
	for(i=G[u];i;i=e[i].next)
	{
		int v=e[i].to;
		if(!label[v]) continue;
		mark[label[v]]=u;
	}
	for(i=1;!label[u];i++)
		if(mark[i]!=u) label[u]=i;
}

int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge2(u,v);
	}
	MCS();
	memset(label,0,sizeof(label));
	memset(mark,0,sizeof(mark));
	for(i=n;i;i--) color(seq[i]);
	int ans=0;
	for(i=1;i<=n;i++) ans=std::max(ans,label[i]);
	printf("%d\n",ans);
	return 0;
}
