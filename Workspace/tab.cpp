#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
typedef long long ll;

ll f(ll x)
{
    ll res=x;
    for(ll p=2;p*p<=x;p++)
        if(x%p==0)
        {  
            ll a=0;
            while(x%p==0) x/=p,a++;
            res/=p;
            res*=p*a+p-a;
        }
    if(x>1)
    {  
        res/=x;  
        res*=x+x-1;  
    }
    return res;
}  
int main()  
{  
	freopen("tab.out","w",stdout);
    int N;
    for(int i=1;i<=1e6;i++) printf("%lld\n",f(i));
    return 0;  
}
