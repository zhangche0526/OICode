#include<iostream>
#include<cstdio>
typedef long long ll;

const int MAXK=2005,P=1e9+7;

int C[MAXK][MAXK],inv[MAXK],B[MAXK];

inline void preTab()
{
	int i,j;C[0][0]=1;
	for(i=1;i<MAXK;i++)
	{
		C[i][0]=1;
		for(j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
	inv[1]=1;for(i=2;i<MAXK;i++) inv[i]=(ll)(P-P/i)*inv[P%i]%P;
	B[0]=1;
	for(i=1;i<MAXK;i++)
	{
		for(j=0;j<i;j++) B[i]=(B[i]+(ll)B[j]*C[i+1][j]%P)%P;
		B[i]=(ll)B[i]*((P-inv[i+1])%P)%P;
	}
}

int np[MAXK];
int calc(int n,int k)
{
	int i,ans=0;np[0]=1;
	for(i=1;i<=k+1;i++) np[i]=(ll)np[i-1]*(n+1)%P;
	for(i=1;i<=k+1;i++) ans=(ans+(ll)C[k+1][i]*B[k+1-i]%P*np[i]%P)%P;
	return (ll)ans*inv[k+1]%P;
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		ll n;int k;scanf("%lld%d",&n,&k);
		printf("%d\n",calc(n%P,k));
	}
	return 0;
}
