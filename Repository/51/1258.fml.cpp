#include<iostream>
#include<cstdio>
typedef long long ll;

const int MAXN=5e4+5,P=1e9+7;

int qpow(int a,ll x)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%P)
		if(x&1) res=(ll)res*a%P;
	return res;
}

int k;ll n,r;
int fac[MAXN],facInv[MAXN],minPF[MAXN],pri[MAXN],pcnt;
inline void preTab()
{
	int i,j;
	for(fac[0]=i=1;i<MAXN;i++) fac[i]=(ll)fac[i-1]*i%P;
	for(facInv[0]=facInv[1]=1,i=2;i<MAXN;i++) facInv[i]=(ll)(P-P/i)*facInv[P%i]%P;
	for(i=2;i<MAXN;i++) facInv[i]=(ll)facInv[i-1]*facInv[i]%P;
	for(i=2;i<MAXN;i++)
	{
		if(!minPF[i]) minPF[i]=pri[++pcnt]=i;
		for(j=1;j<=pcnt&&pri[j]<=i&&pri[j]*i<MAXN;j++)
			minPF[pri[j]*i]=pri[j];
	}
}

int xk[MAXN],f[MAXN],prfPrd[MAXN],sufPrd[MAXN];

int calc()
{
	int i;
	for(prfPrd[0]=i=1;i<=k+1;i++) prfPrd[i]=(ll)prfPrd[i-1]*((n-i+1)%P)%P;
	for(sufPrd[k+1]=1,i=k;i>=0;i--) sufPrd[i]=(ll)sufPrd[i+1]*((n-i-1)%P)%P;
	int res=0;
	for(i=0;i<=k+1;i++)
	{
		int prd=(ll)f[i]*facInv[i]%P*facInv[k-i+1]%P*prfPrd[i]%P*sufPrd[i]%P;
		if((k-i+1)&1) prd=(P-prd)%P;
		res=(res+prd)%P;
	}
	return res;
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int i;
		scanf("%lld%d",&n,&k);
		for(xk[1]=f[1]=1,i=2;i<=k+1;i++)
		{
			if(minPF[i]==i) xk[i]=qpow(i,k);
			else xk[i]=(ll)xk[minPF[i]]*xk[i/minPF[i]]%P;
			f[i]=(f[i-1]+xk[i])%P;
		}
		if(n<=(ll)k+1) {printf("%d\n",f[n]);continue;}
		printf("%d\n",calc());
	}
	return 0;
}
