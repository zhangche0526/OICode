#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long ll;
const int MAXN=1e5+5,MAXM=2e5+5,P=1e9+7;
 
int N,M,S,T;
 
struct E{int next,to,val;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}
 
ll fS[MAXN],dS[MAXN],fT[MAXN],dT[MAXN];
 
struct HN{int id;ll v;};
bool operator <(const HN &a,const HN &b){return a.v>b.v;}
std::priority_queue<HN> heap;
bool inS[MAXN];
void dijkstra(int v0,ll *f,ll *d)
{
	memset(inS,0,sizeof inS);
	memset(d,0x3f,sizeof dS);
	d[v0]=0,f[v0]=1;heap.push((HN){v0,0});
	while(!heap.empty())
	{
		int u=heap.top().id;heap.pop();
		if(inS[u]) continue;inS[u]=true;
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(inS[v]) continue;
			if(d[v]>d[u]+e[i].val)
			{
				f[v]=f[u];
				d[v]=d[u]+e[i].val;
				heap.push((HN){v,d[v]});
			}
			else if(d[v]==d[u]+e[i].val) f[v]=(f[v]+f[u])%P;
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
	int ans=(ll)fS[T]*fS[T]%P;
	for(i=1;i<=N;i++)
		if(dS[i]==dT[i]&&dS[i]+dT[i]==dS[T])
			ans=(ans+P-fS[i]*fS[i]%P*fT[i]%P*fT[i]%P)%P;
	for(i=1;i<=M;i++)
	{
		int u=a[i].u,v=a[i].v,w=a[i].w;
		if(dS[u]>dS[v]) std::swap(u,v);
		if(dS[u]<dS[T]>>1&&dT[v]<dT[S]>>1&&dS[u]+dT[v]+w==dS[T])
			ans=(ans+P-fS[u]*fS[u]%P*fT[v]%P*fT[v]%P)%P;
	}
	printf("%d",ans);
	return 0;
}
