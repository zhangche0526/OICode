#include<iostream>
#include<cstdio>
typedef long long ll;

const int MAXN=2e5+10,P=985661441;

int qpow(int a,ll x)
{
	int res=1;
	for(;x;x>>=1LL,a=(ll)a*a%P)
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

int xk[MAXN],f[MAXN],F[MAXN],prfPrd[MAXN],sufPrd[MAXN];

int cal1()
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

int cal2()
{
	int i;
	int rInv=qpow(r,P-2);
	int suma=1,sumb=0;prfPrd[0]=1,sufPrd[0]=0;
	for(i=1;i<=k+1;i++)
	{
		prfPrd[i]=(ll)prfPrd[i-1]*rInv%P;
		sufPrd[i]=(ll)(sufPrd[i-1]+xk[i])*rInv%P;
		int coe=(ll)fac[k+1]%P*facInv[i]%P*facInv[k+1-i]%P;
		if(i&1) coe=(P-coe)%P;
		suma=(suma+(ll)coe*prfPrd[i]%P)%P;
		sumb=(sumb+(ll)coe*sufPrd[i]%P)%P;
	}
	int x=(ll)(P-sumb)*qpow(suma,P-2)%P;
	for(i=0;i<=k;i++) F[i]=((ll)prfPrd[i]*x+sufPrd[i])%P;

	for(prfPrd[0]=i=1;i<=k;i++) prfPrd[i]=(ll)prfPrd[i-1]*((n-i+1)%P)%P;
	for(sufPrd[k]=1,i=k-1;i>=0;i--) sufPrd[i]=(ll)sufPrd[i+1]*((n-i-1)%P)%P;
	int res=0;
	for(i=0;i<=k;i++)
	{
		int prd=(ll)F[i]*facInv[k-i]%P*facInv[i]%P*prfPrd[i]%P*sufPrd[i]%P;
		if((k-i)&1) prd=(P-prd)%P;
		res=(res+prd)%P;
	}
	res=((ll)res*qpow(r,n)%P+P-F[0])%P;
	res=(ll)res*r%P;
	return res;
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int i,rPrd;
		scanf("%d%lld%lld",&k,&n,&r);r%=P;
		if(!r) {puts("0\n");continue;}
		for(xk[1]=1,f[1]=r,rPrd=r*r%P,i=2;i<=k+1;i++,rPrd=(ll)rPrd*r%P)
		{
			if(minPF[i]==i) xk[i]=qpow(i, k);
			else xk[i]=(ll)xk[minPF[i]]*xk[i/minPF[i]]%P;
			f[i]=(f[i-1]+(ll)xk[i]*rPrd%P)%P;
		}
		if(n<=(ll)k+1) {printf("%d\n",f[n]);continue;}
		if(r==1) printf("%d\n",cal1());
		else printf("%d\n",cal2());
	}
	return 0;
}

