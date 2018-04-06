#include<iostream>
#include<cstdio>

const int MAXN=1e4+5;

int n;
double f[MAXN],g[MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=n-1;~i;i--)
	{
		g[i]=g[i+1]+(double)n/(n-i);
		f[i]=f[i+1]+g[i+1]+g[i]*i/(n-i)+(double)n/(n-i);
	}
	printf("%.2lf",f[0]);
	return 0;
}
