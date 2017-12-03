#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
typedef long long ll;

ll f(ll x)
{
    ll res=x;
    for(ll i=2;i*i<=x;i++)
        if(x%i==0)
        {  
            ll cnt=0;
            while(x%i==0) x/=i,cnt++;
            res/=i;
            res*=i*cnt+i-cnt;
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
	int N;
    while(scanf("%lld",&N)!=EOF)
		printf("%lld\n",f(N));
    return 0;  
}  
