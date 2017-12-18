#include<iostream>
#include<cstdio>

const int MAXN=2005,P=1e9+7;

int n,k;
int f[MAXN][MAXN];

int main()
{
	int i,j;
	f[1][n-k]=1;for(i=1;i<n-k;i++) f[1][n-k]=(f[1][n-k]<<1)%P;
	for(i=1;i<=n;i++)
	return 0;
}
