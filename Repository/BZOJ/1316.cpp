/**************************************************************
    Problem: 1316
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1208 ms
    Memory:2240 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
 
const int MAXN=1e4+5,MAXQ=105;
 
int n,q;
int qry[MAXQ],ans[MAXQ];
 
struct E{int next,to,val;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v,int w){e[++ecnt]=(E){G[u],v,w};G[u]=ecnt;}
void addEdge2(int u,int v,int w){addEdge(u,v,w);addEdge(v,u,w);}
 
bool vis[MAXN];int rt;
int mxv[MAXN],mnv,sz[MAXN];
 
void calSz(int u,int la)
{
    sz[u]=1,mxv[u]=0;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==la||vis[v]) continue;
        calSz(v,u);
        sz[u]+=sz[v];
        umx(mxv[u],sz[v]);
    }
}
 
void calRt(int u,int la,int r)
{
    umx(mxv[u],sz[r]-sz[u]);
    if(mxv[u]<mnv) mnv=mxv[u],rt=u;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==la||vis[v]) continue;
        calRt(v,u,r);
    }
}
 
int dis[MAXN],dcnt;
void calDis(int u,int la,int d)
{
    dis[++dcnt]=d;
    for(int i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;
        if(v==la||vis[v]) continue;
        calDis(v,u,d+e[i].val);
    }
}
 
void upd(int u,int d,int flg)
{
    dcnt=0;calDis(u,0,d);
    std::sort(dis+1,dis+dcnt+1);
    int i,k;
    for(i=1;i<=q;i++)
    {
        int l,r;k=qry[i];
        int cnt0=0,cnt1=0;
        for(l=1,r=dcnt;l<r;l++)
        {
            while(dis[l]+dis[r]>=k&&l<r) r--;
            cnt0+=r-l;
        }
        for(l=1,r=dcnt;l<r;l++)
        {
            while(dis[l]+dis[r]>k&&l<r) r--;
            cnt1+=r-l;
        }
        ans[i]+=flg*(cnt1-cnt0);
    }
}
 
void treeDC(int u)
{
    mnv=n;calSz(u,0);calRt(u,0,u);
    upd(rt,0,1);vis[rt]=true;
    for(int i=G[rt];i;i=e[i].next)
    {
        int v=e[i].to;
        if(vis[v]) continue;
        upd(v,e[i].val,-1);
        treeDC(v);
    }
}
 
int main()
{
    int i;scanf("%d%d",&n,&q);
    for(i=1;i<n;i++)
    {
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        addEdge2(u,v,w);
    }
    for(i=1;i<=q;i++) scanf("%d",qry+i);
    treeDC(1);
    for(i=1;i<=q;i++)
        if(qry[i]) puts(ans[i]?"Yes":"No");
        else puts("Yes");
    return 0;
}
