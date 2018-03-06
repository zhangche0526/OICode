#include<iostream>
#include<cstdio>
typedef long long ll;
const int P=100003;

ll M,N;
ll qpow(ll a,ll n)
{
	ll res=1;
	for(ll i=1;i<=N;i<<=1,a=(a*a)%P)
		if(i&n) res=(res*a)%P;
	return res;
}

int main()
{
    scanf("%lld%lld",&M,&N);
    ll ans=qpow(M,N)-(M*qpow(M-1,N-1))%P;
    printf("%lld",(ans+P)%P);
    return 0;
}
