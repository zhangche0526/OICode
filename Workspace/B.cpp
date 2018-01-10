#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
typedef long long ll;
const int P=998244353;

ll n;int lgn;

std::map<ll,int> f[2],g[2];

int dp(bool c,ll len)
{
	if(f[c][len]) return f[c][len];
	int rL=len>>1,lL=len-rL;
	if(c) f[c][len]=(ll)f[0][lL]*f[1][rL]%P+(ll)f[1][lL]*f[0][rL]%P;
	else f[c][len]=(ll)f[1][lL]*f[1][rL]%P;
	return f[c][len];
}

int main()
{
	int i;
	scanf("%lld",&n);
	f[0][n]=f[1][n]=1;
	int ans=(dp(0,n)+dp(1,n))%P;
	printf("%d",ans);
	return 0;
}
