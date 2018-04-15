#include<iostream>
#include<cstdio>
#include<cmath>

const int MAXN=105;
const double eps=1e-8;

int n;
double equ[MAXN][MAXN];

bool guass()
{
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		int num=i;
		for(j=i;j<=n;j++)
			if(std::fabs(equ[num][i])<std::fabs(equ[j][i]))
				num=j;
		std::swap(equ[i],equ[num]);
		if(!equ[i][i]) return false;
		for(j=i+1;j<=n;j++)
		{
			double t=equ[j][i]/equ[i][i];
			for(k=i;k<=n+1;k++)
				equ[j][k]-=equ[i][k]*t;
		}
	}
	for(i=n;i;i--)
	{	
		for(j=i+1;j<=n;j++)
			equ[i][n+1]-=equ[i][j]*equ[j][n+1];
		equ[i][n+1]/=equ[i][i];
	}
	return true;
}

int main()
{
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) for(j=1;j<=n+1;j++)
		scanf("%lf",&equ[i][j]);
	if(guass()) for(i=1;i<=n;i++) printf("%.2lf\n",equ[i][n+1]);
	else puts("No Solution");
	return 0;
}
