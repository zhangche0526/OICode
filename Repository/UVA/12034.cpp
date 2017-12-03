#include<iostream>
#include<cstdio>

const int MAXN=1e3,P=10056;

int C[MAXN+5][MAXN+5],f[MAXN+5];
inline void preTab()
{
	int i,j;
	C[0][0]=1;
	for(i=1;i<=MAXN;i++)
	{
		C[i][0]=C[i][i]=1;
		for(j=1;j<i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
	}
	f[0]=1;
	for(i=1;i<=MAXN;i++)
		for(j=1;j<=i;j++)
			f[i]=(f[i]+C[i][j]*f[i-j])%P;
}

int main()
{
	preTab();
	int T,Case;scanf("%d",&T);
	for(Case=1;Case<=T;Case++)
	{
		int n;scanf("%d",&n);
		printf("Case %d: %d\n",Case,f[n]);
	}
	return 0;
}
