/**************************************************************
    Problem: 4017
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:13256 ms
    Memory:3372 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
const int MAXN=1e5+5,MOD=998244353;
 
int n;
//---------------------------------------------------
int xsum[MAXN];
ll solve1()
{
    int i,k,cnt[2];
    ll res=0;
    for(k=0;k<=30;k++)
    {
        cnt[0]=cnt[1]=0;
        ll tmp=0;
        for(i=0;i<=n;i++)
        {
            bool t=xsum[i]&(1<<k);
            tmp+=cnt[t^1];
            cnt[t]++;
        }
        res=(res+((1LL<<k)*tmp)%MOD)%MOD;
    }
    return res;
}
//---------------------------------------------------
struct FT
{
    bool na[MAXN];
    FT(){memset(na,0,sizeof(na));}
    int lowbit(int x){return x&(-x);}
    void change(int x)
    {
        if(x==-1) return;
        for(++x;x<=n+1;x+=lowbit(x)) na[x]^=1;
    }
    bool get(int x)
    {
        bool res=0;
        for(++x;x;x-=lowbit(x)) res^=na[x];
        return res;
    }
} ft;
 
ll p[MAXN],sum[MAXN];
int find(ll x)
{
    int l=0,r=n,mid;
    int res=-1;
    while(l<=r)
    {
        mid=l+r>>1;
        if(p[mid]<=x) l=mid+1,res=mid;
        else r=mid-1;       
    }
    return res;
}
ll solve2()
{
    int i,k;
    ll res=0;
    for(k=0;(1LL<<k)<=sum[n];k++)
    {
        bool ok=false;
        for(i=0;i<=n;i++) p[i]=sum[i]&((1LL<<k+1)-1);
        std::sort(p,p+n+1);
        ft=FT();
        for(i=0;i<=n;i++)
        {
            ll now=sum[i]&((1LL<<k+1)-1);
            ok^=ft.get(find(now-(1LL<<k)))^ft.get(find(now))^ft.get(find(now+(1LL<<k)));
            ft.change(find(now));
        }
        if(ok) res|=(1LL<<k);
    }
    return res;
}
//---------------------------------------------------
int main()
{
    int i,x;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",&x),xsum[i]=xsum[i-1]^x,sum[i]=sum[i-1]+x;
    printf("%lld %lld\n",solve1(),solve2());
    return 0;
}
