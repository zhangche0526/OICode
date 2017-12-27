#include<iostream>
#include<cstdio>

typedef long long ll;

inline ll ceil(ll a,ll b){return (a+b-1)/b;}

int main()
{
	bool ans=false;
	ll n;scanf("%I64d",&n);
	ll l=ceil(n+1,9),r=n;
	while(l>1) l=ceil(l,2),r/=9,ans^=1;
	if(ans) puts("Stan wins.");
	else puts("Ollie wins.");
	return 0;
}
