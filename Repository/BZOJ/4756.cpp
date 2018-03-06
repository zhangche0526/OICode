/**************************************************************
    Problem: 4756
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:332 ms
    Memory:7072 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<algorithm>
 
const int MAXN=1e5+5;
 
int N;
int p[MAXN];
 
struct E{int next,to;} e[MAXN];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
 
int seq[MAXN],scnt,pos[MAXN],sz[MAXN];
bool cmp(const int &x,const int &y){return p[x]>p[y];}
 
void dfs(int u)
{
    seq[++scnt]=u;pos[u]=scnt;sz[u]=1;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        dfs(v);
        sz[u]+=sz[v];
    }
}
 
int na[MAXN];
void add(int x){for(;x<=N;x+=x&(-x)) na[x]++;}
int sum(int x){int res=0;for(;x;x-=x&(-x)) res+=na[x];return res;}
 
int ans[MAXN];
int main()
{
    int i;
    scanf("%d",&N);
    for(i=1;i<=N;i++) scanf("%d",p+i);
    for(i=2;i<=N;i++)
    {
        int f;scanf("%d",&f);
        addEdge(f,i);
    }
    dfs(1);
    std::sort(seq+1,seq+1+N,cmp);
    for(i=1;i<=N;i++)
    {
        int u=seq[i];
        int l=pos[u],r=pos[u]+sz[u]-1;
        ans[u]=sum(r)-sum(l);
        add(l);
    }
    for(i=1;i<=N;i++) printf("%d\n",ans[i]);
    return 0;
}
