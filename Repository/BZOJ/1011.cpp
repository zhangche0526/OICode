#include<iostream>
#include<cstdio>

const int MAXN=1e5+5;

int n;
double a,A[MAXN],Asum[MAXN];

int main()
{
	double ans;
	scanf("%d%lf",&n,&a);
	for(int j=1;j<=n;j++)
	{
		int i=a*j+1e-8;
		scanf("%lf",&A[j]);
		ans=0;
		if(j<=500)
			for(int k=1;k<=i;k++)
				ans+=A[k]*A[j]/(j-k);
		else ans=Asum[i]*A[j]/(j-i/2);
		printf("%f\n",ans);
		Asum[j]=Asum[j-1]+A[j];
	}
	return 0;
}
