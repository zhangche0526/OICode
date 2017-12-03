#include<iostream>
#include<cstdio>
typedef long long ll;
const ll MAXN=3e6+5;

ll N,P;
ll inv[MAXN];

int main()
{
	int i;
	scanf("%lld%lld",&N,&P);
	inv[1]=1;
	for(i=2;i<=N;i++)
		inv[i]=((P-P/i)*inv[P%i])%P;
	for(i=1;i<=N;i++)
		printf("%lld\n",inv[i]);
	return 0;
}
