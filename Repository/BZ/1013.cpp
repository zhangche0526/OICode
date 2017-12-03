#include<iostream>
#include<cstdio>
#include<cmath>

const int MAXN=15;
const double eps=1e-8;

int n;
double a[MAXN],equ[MAXN][MAXN],ans[MAXN];

void guass()
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		int num=i;
		for(j=i;j<n;j++)
			if(std::fabs(equ[num][i])<std::fabs(equ[j][i]))
				num=j;
		for(j=i;j<=n;j++)
			std::swap(equ[i][j],equ[num][j]);
		for(j=i+1;j<n;j++)
			if(fabs(equ[i][i]-equ[j][i])>eps)
			{
				double t=equ[j][i]/equ[i][i];
				for(k=i;k<=n;k++)
					equ[j][k]-=equ[i][k]*t;
			}
	}
	for(i=n-1;i>=0;i--)
	{
		ans[i]=equ[i][n]/equ[i][i];
		for(j=i;j>=0;j--)
			equ[j][n]-=(equ[j][i]*ans[i]);
	}
}

int main()
{
	int i,j;
	scanf("%d",&n);
	for(i=0;i<n;i++)
		scanf("%lf",a+i);
	double ra;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			scanf("%lf",&ra);
			equ[i][j]=2*(a[j]-ra);
			equ[i][n]+=a[j]*a[j]-ra*ra;
		}
	guass();
	for(i=0;i<n-1;i++)
		printf("%.3f ",ans[i]);
	printf("%.3f\n",ans[i]);
	return 0;
}
