/**************************************************************
    Problem: 1023
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:256 ms
    Memory:7076 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
using namespace std;
 
const int MAXN=5e4+5,MAXM=MAXN<<1;
 
int n,m;
struct E{int next,to;} e[MAXM<<1];int ecnt,G[MAXN];
void addEdge(int u,int v)
{
    e[++ecnt]=(E){G[u],v};G[u]=ecnt;
    e[++ecnt]=(E){G[v],u};G[v]=ecnt;
}
int ans;
int f[MAXN];
int dfn[MAXN],dcnt,low[MAXN],dpt[MAXN],fa[MAXN];
int que[MAXN<<1],a[MAXN<<1];
void solve(int x,int y)
{
    int cnt=dpt[y]-dpt[x]+1,head=1,tail=1,i;
    for(i=y;i!=x;i=fa[i]) a[cnt--]=f[i];a[1]=f[x];
    cnt=dpt[y]-dpt[x]+1;
    for(i=1;i<=cnt;i++) a[i+cnt]=a[i];
    que[1]=1;
    for(i=2;i<=cnt+(cnt>>1);i++)
    {
        if(i-que[head]>(cnt>>1)) head++;
        ans=max(ans,a[i]+i+a[que[head]]-que[head]);
        while(head<=tail&&a[i]-i>=a[que[tail]]-que[tail]) tail--;
        que[++tail]=i;
    }
    for(i=2;i<=cnt;i++) f[x]=max(f[x],a[i]+min(i-1,cnt-i+1));
}
 
void dfs(int u)
{
    int i;
    dfn[u]=low[u]=++dcnt;
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa[u]) continue;
        if(!dfn[v]) {fa[v]=u;dpt[v]=dpt[u]+1;dfs(v);}
        low[u]=min(low[u],low[v]);
        if(low[v]>dfn[u]) ans=max(ans,f[u]+f[v]+1),f[u]=max(f[u],f[v]+1);
        //对树边的更新
    }
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(fa[v]!=u&&dfn[u]<dfn[v])//遍历非树边，处理环
            solve(u,v);
    }
}
 
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)
    {
        int k;scanf("%d",&k);
        int u,v;scanf("%d",&u);
        for(j=2;j<=k;j++) scanf("%d",&v),addEdge(u,v),u=v;
    }
    dfs(1);printf("%d\n",ans);
    return 0;
}
