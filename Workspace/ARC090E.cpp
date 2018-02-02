#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long ll;
const int MAXN=1e5+5,MAXM=2e5+5;

int N,M,S,T;

struct E{int next,to,val;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge(int u,int v,int w){addEdge(u,v);addEdge(v,u);}

int fS[MAXN],dS[MAXN],fT[MAXN],dT[MAXN];

struct HN{int id,v;};
bool operator <(const HN &a,const HN &b){return a.v>b.v;}
std::priority_queue<int> heap;
bool inS[MAXN];
void dijkstra(int v0,int *f,int *d)
{
	memset(inS,0,sizeof inS);
	memset(d,0x3f,sizeof d);
	d[v0]=0;que.push((HN){v0,0});
	while(!heap.enpty())
	{
		int u=heap.top().id;heap.pop();
		if(inS[u]) continue;inS[u]=true;
		for(i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(inS[v]) continue;
			if(d[v]==d[u]+e[i].val) f[v]++;
			if(d[v]>d[u]+e[i].val)
			{
				d[v]=d[u]+e[i].val;
				heap.push(v,d[v]);
			}
		}
	}
}

struct A{int u,v,w;} a[MAXM];
int main()
{
	int i;scanf("%d%d%d%d",&N,&M,&S,&T);
	for(i=1;i<=M;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		addEdge2(u,v,w);a[i]=(A){u,v,w};
	}
	dijkstra(S,fS,dS);
	dijkstra(T,fT,dT);
	ll ans=(ll)fS[T]*fS[T];
	for(i=1;i<=N;i++)
		if(dS[i]==dT[i]&&dS[i]==dS[T]>>1)
			ans-=fS[i]*fS[i]*fT[i]*fT[i];
	for(i=1;i<=M;i++)
	{
		int u=a[i].u,v=a[i].v,w=a[i].w;
		if(dS[u]<dS[T]>>1&&dT[v]<dT[S]>>1&&dS[u]+dT[v]+w==dS[T])
			ans-=fS[u]*fS[u]*fT[v]*fT[v];
	}
	printf("%lld",ans);
	return 0;
}
