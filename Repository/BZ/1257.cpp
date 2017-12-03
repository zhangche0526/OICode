#include<iostream>
#include<cstdio>
typedef long long ll;
 
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    ll ans=0;
    if(n>k)
    {
        ans=(ll)k*(n-k);
        n=k;
    }
    for(int l=1,t,r;l<=n;l=r+1)
    {
        r=k/(k/l);
        if(r>=n) r=n;
        ans+=(ll)(r-l+1)*k-(ll)(r-l+1)*(l+r)/2*(k/l);
    }
    printf("%lld",ans);
    return 0;
}
