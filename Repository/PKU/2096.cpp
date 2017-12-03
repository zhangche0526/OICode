#include<iostream>
#include<cstdio>

const int MAXN=1e3+5;

double n,m;

double dp[MAXN][MAXN];

int main()
{
	int i,j;
	while(scanf("%lf%lf",&n,&m)!=EOF)
	{
		for(i=n;i>=0;i--)
			for(j=m;j>=0;j--)
				if(!(i==n&&j==m))
					dp[i][j]=(1+(n-i)*j/n/m*dp[i+1][j]+i*(m-j)/n/m*dp[i][j+1]+(n-i)*(m-j)/n/m*dp[i+1][j+1])/(1-i*j/n/m);
		printf("%.4lf\n",dp[0][0]);
	}
}
