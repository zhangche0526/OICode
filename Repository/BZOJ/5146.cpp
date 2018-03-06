/**************************************************************
    Problem: 5146
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1288 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
typedef long long ll;
const int P=1e9+7;
 
ll qpow(ll a,ll x)
{
    ll res=1;
    for(;x;x>>=1,a=a*a%P)
        if(x&1) res=res*a%P;
    return res;
}
 
int main()
{
    ll n;scanf("%lld",&n);
    ll ans=qpow(qpow(2,P-2),n-1);
    n%=P;
    ans=ans*n%P*((n+P-2)%P)%P;
    printf("%lld",ans);
    return 0;
}
