/**************************************************************
    Problem: 2809
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1216 ms
    Memory:7324 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
using std::max;
typedef long long ll;
inline void umx(ll &a,ll b){a=max(a,b);}
 
const int MAXN=1e5+5;
 
int n,m;
int V[MAXN],W[MAXN];
struct E{int next,to;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
struct LT{int lc,rc,d;} t[MAXN];int rt[MAXN];
int merge(int x,int y)
{
    if(!x) return y;
    if(!y) return x;
    if(V[x]<V[y]) std::swap(x,y);
    t[x].rc=merge(t[x].rc,y);
    if(t[t[x].lc].d<t[t[x].rc].d) std::swap(t[x].lc,t[x].rc);
    t[x].d=t[t[x].rc].d+1;
    return x;
}
ll sum[MAXN],ans;
int sz[MAXN];
void dfs(int u)
{
    rt[u]=u,sum[u]=V[u],sz[u]=1;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        dfs(v);
        rt[u]=merge(rt[u],rt[v]);
        sum[u]+=sum[v],sz[u]+=sz[v];
    }
    while(sum[u]>m)
    {
        sum[u]-=V[rt[u]],sz[u]--;
        rt[u]=merge(t[rt[u]].lc,t[rt[u]].rc);
    }
    umx(ans,(ll)W[u]*sz[u]);
}
 
int main()
{
    int i;scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)
    {
        int f;scanf("%d%d%d",&f,V+i,W+i);
        if(f) addEdge(f,i);
    }
    t[0].d=0;
    dfs(1);
    printf("%lld",ans);
    return 0;
}
