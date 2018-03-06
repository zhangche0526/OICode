/**************************************************************
    Problem: 1367
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:7456 ms
    Memory:36444 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
 
const int MAXN=1e6+5;
 
int n;
int a[MAXN];
 
int rt[MAXN],rtcnt;
struct LT{int lc,rc,w,d,sz;} t[MAXN];
int merge(int x,int y)
{
    if(!x) return y;
    if(!y) return x;
    if(t[x].w<t[y].w) std::swap(x,y);
    t[x].sz+=t[y].sz;
    t[x].rc=merge(t[x].rc,y);
    if(t[t[x].lc].d<t[t[x].rc].d) std::swap(t[x].lc,t[x].rc);
    t[x].d=t[t[x].rc].d+1;
    return x;
}
 
int main()
{
    int i;scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",a+i),a[i]-=i;
    int rgcnt=0;static int L[MAXN],R[MAXN];t[0].d=-1;
    for(i=1;i<=n;i++)
    {
        rt[++rgcnt]=++rtcnt;
        t[rt[rgcnt]].w=a[i],t[rt[rgcnt]].sz=1;
        L[rgcnt]=R[rgcnt]=i;
        while(rgcnt>1&&t[rt[rgcnt]].w<t[rt[rgcnt-1]].w)
        {
            rt[rgcnt-1]=merge(rt[rgcnt-1],rt[rgcnt]),R[rgcnt-1]=R[rgcnt];
            rgcnt--;
            while(t[rt[rgcnt]].sz<<1 > R[rgcnt]-L[rgcnt]+1 +1) rt[rgcnt]=merge(t[rt[rgcnt]].lc,t[rt[rgcnt]].rc);
        }
    }
    ll ans=0;
    for(int r=1;r<=rgcnt;r++)
        for(i=L[r];i<=R[r];i++)
            ans+=(ll)abs(t[rt[r]].w-a[i]);
    printf("%lld",ans);
    return 0;
}
?
