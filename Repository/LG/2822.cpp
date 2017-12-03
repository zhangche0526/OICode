#include<iostream>
#include<cstdio>

const int MAXN=2e3;

int K;
int C[MAXN+5][MAXN+5],sum[MAXN+5][MAXN+5];
inline void preTab()
{
	int i,j;C[0][0]=1;
	for(i=1;i<=MAXN;i++)
	{
		C[i][0]=1;
		int isum=0;
		for(j=1;j<i;j++)
		{
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%K;
			if(!C[i][j]) isum++;
			sum[i][j]=sum[i-1][j]+isum;
		}
		C[i][i]=1,sum[i][i]=sum[i-1][j-1]+isum;
	}
}

int main()
{
	int T;scanf("%d%d",&T,&K);
	preTab();
	while(T--)
	{
		int n,m;scanf("%d%d",&n,&m);
		if(n<m) m=n;
		printf("%d\n",sum[n][m]);
	}
}
