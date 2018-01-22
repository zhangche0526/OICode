#include<iostream>
#include<cstdio>

typedef long long ll;

const int P=1e6+3;

int fac[P],facInv[P];
inline void preTab()
{
	int i;
	for(fac[0]=i=1;i<P;i++) fac[i]=(ll)fac[i-1]*i%P;
	for(facInv[1]=1,i=2;i<P;i++) facInv[i]=(ll)(P-P/i)*facInv[P%i]%P;
	for(facInv[0]=i=1;i<P;i++) facInv[i]=(ll)facInv[i-1]*facInv[i]%P;
}

int C(int n,int m)
{
	if(n<m) return 0;
	if(n<P&&m<P) return (ll)fac[n]*facInv[n-m]%P*facInv[m]%P;
	return (ll)C(n%P,m%P)*C(n/P,m/P)%P;
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,l,r;scanf("%d%d%d",&n,&l,&r);
		printf("%d\n",(C(n+r-l+1,n)-1+P)%P);
	}
	return 0;
}
