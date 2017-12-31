#pra\
gma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
const int MAXN=1005,MAXM=10005,INF=1061109567;

int n,m;

struct E{int next,to,*val;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int *w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int *w){addEdge(u,v,w);addEdge(v,u,w);}
int W[MAXM];

template <typename T>
class HP
{
public:
    static const int rt=1;
    T t[MAXN];int sz;
    void push(T x)
    {
        t[++sz]=x;
        for(int u=sz;u>>1;u>>=1)
        {
            if(!(t[u]<t[u>>1])) break;
            std::swap(t[u],t[u>>1]);
        }
    }
    void pop()
    {
        t[rt]=t[sz--];
        for(int u=1,v=2;v<=sz;u=v,v=u<<1)
        {
            if(v<sz&&t[v+1]<t[v]) v++;
            if(t[u]<t[v]) break;
            std::swap(t[u],t[v]);
        }
    }
    bool empty(){return !sz;}
    T top(){return t[rt];}
};

struct HN{int u,d;HN(){}HN(int u,int d):u(u),d(d){}};
bool operator <(const HN &a,const HN &b){return a.d<b.d;}
HP<HN> heap;
int dis[MAXN];bool inS[MAXN];
int dijkstra()
{
    int i;
    memset(inS,false,sizeof inS);
    memset(dis,0x3f,sizeof dis);dis[1]=0;
    heap.push(HN(1,0));
    while(!heap.empty())
    {
        int u=heap.top().u,d=heap.top().d;heap.pop();
        if(inS[u]) continue;inS[u]=true;
        for(i=G[u];i;i=e[i].next)
        {
            int v=e[i].to;
            if(inS[v]) continue;
            if(dis[v]>d+*e[i].val)
            {
                dis[v]=d+*e[i].val;
                heap.push(HN(v,dis[v]));
            }
        }
    }
    return dis[n];
}

int main()
{
    int i;scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)
    {
        int u,v;scanf("%d%d%d",&u,&v,W+i);
        addEdge2(u,v,W+i);
    }
    int d0=dijkstra();
    int ans=0;
    for(i=1;i<=m;i++)
    {
        int law=W[i];W[i]<<=1;
        umx(ans,dijkstra()-d0);
        W[i]=law;
    }
    printf("%d",ans);
    return 0;
}
