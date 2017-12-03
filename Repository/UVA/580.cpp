#include<iostream>
#include<cstdio>

const int MAXN=30;

int f[MAXN+5],g[MAXN+5];

inline void preTab()
{
	int i,j;
	f[0]=f[1]=f[2]=0;
	g[0]=1,g[1]=2,g[2]=4;
	for(i=3;i<=MAXN;i++)
	{
		f[i]=(1<<i-3);
		for(j=2;j<=i-2;j++)
			f[i]+=g[j-2]*(1<<i-j-2);
		g[i]=(1<<i)-f[i];
	}
}

int main()
{
	preTab();
	int n;
	while(scanf("%d",&n)&&n)
		printf("%d\n",f[n]);
	return 0;
}
