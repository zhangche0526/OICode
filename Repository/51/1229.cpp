#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXK=2005,P=1e9+7;

int C[MAXK][MAXK],inv[MAXK],B[MAXK];
inline void preTab()
{
	int i,j;

	for(C[0][0]=i=1;i<MAXK;i++)
		for(C[n][0]=j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;

	inv[1]=1;for(i=2;i<MAXK;i++) inv[i]=(ll)(P-P/i)*inv[P%i]%P;

	for(B[0]=i=1;i<=MAXN;i++)
	{
		for(j=0;j<i;j++) B[i]=(B[i]+(ll)C[i+1][j]*B[j]%P)%P;
		B[i]=(ll)B[i]*(P-inv[i+1])%P;
	}
}

int S(int n,int k)
{
	
}

int np[MAXK];

void solve(int n,int k)
{
	int res=0;
	for(np[0]=i=1;i<=k;i++) np[i]=(ll)np[i-1]*(n+1);
	for(i=1;i<=k+1;i++) 
}

int calc(int n,int k,int r)
{
	if(r==1)
	{

	}
}

int main()
{

}
