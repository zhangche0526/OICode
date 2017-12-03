#include<iostream>
#include<cstdio>
#include<climits>
#include<cmath>
typedef long long ll;
const int MRT=50;
const ll INF=~0ULL>>1;

ll rand(ll l,ll r){return ((ll)((double)rand()/32767.0))*INF%(r-l+1)+l;}
ll qpow(ll a,ll x,ll p)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%p)
		if(x&1) res=(ll)res*a;
	return res;
}

bool MR(ll x)
{
	if(x<2) return false;
	ll a,b=x-1,la;
	int k=0;
	for(;(~b)&1;b>>=1,++k);
	for(int i=1;i<=MRT;++i)
	{
		a=rand(2,x-1);
		a=qpow(a,b,x);
		for(int j=1;j<=k;++j)
		{
			la=a;
			a=qpow(a,2,x);
			if(a==1)
			{
				if(la!=1&&la!=x-1)
					return false;
				else if(la==1) break;
			}
		}
		if(a!=1) return false;
	}
	return true;
}
