#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=20;

ll f[MAXN+5][MAXN+5][MAXN+5];

inline void preTab()
{
	int i,j,k;
	f[1][1][1]=1;
	for(i=2;i<=MAXN;i++)
		for(j=0;j<=i;j++)
			for(k=0;k<=i;k++)
				f[i][j][k]=f[i-1][j-1][k]+f[i-1][j][k-1]+f[i-1][j][k]*(i-2);
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,l,r;scanf("%d%d%d",&n,&l,&r);
		printf("%lld\n",f[n][l][r]);
	}
	return 0;
}
