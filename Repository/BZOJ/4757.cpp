/**************************************************************
    Problem: 4757
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1632 ms
    Memory:2080 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cmath>
typedef long long ll;
 
const int MAXN=1e5+5;
const double eps=1e-9;
 
ll n,k;
 
double a[MAXN];
bool check(double t)
{
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        double c=0.5*(std::sqrt(1.0+4.0*a[i]/t)-1.0);
        c=std::ceil(c);sum+=c;
        if(sum>k) return false;
    }
    return true;
}
 
int main()
{
    int i;ll x;
    scanf("%lld%lld",&n,&k);
    for(i=1;i<=n;i++)
    {
        scanf("%lld",&x);
        a[i]=x;
    }
    double l=eps,r=1e12;
    while(r-l>eps)
    {
        double mid=(l+r)*0.5;
        if(check(mid)) r=mid;
        else l=mid;
    }
    double t=r;
    ll sum=0;double ans=0;
    for(i=1;i<=n;i++)
    {
        double c=0.5*(std::sqrt(1.0+4.0*a[i]/t)-1.0);
        c=std::ceil(c);sum+=c;
        ans+=a[i]/c;
    }
    printf("%.0lf",ans-(k-sum)*t);
}
