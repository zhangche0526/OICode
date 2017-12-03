#include<iostream>
#include<cstdio>
#include<cstring>

int f[10][10];

inline void initDp()
{
	int i,j,k;
	f[0][0]=1;
	for(i=1;i<=7;i++)
		for(j=0;j<=9;j++)
			for(k=0;k<=9;k++)
				if(j!=4&&!(j==6&&k==2))
					f[i][j]+=f[i-1][k];
}

int num[10];

int solve(int x)
{
	memset(num,0,sizeof(num));
	int res=0,len=0;
	while(x) num[++len]=x%10,n/=10;
	for(i=len;i>=1;i--)
	{
		for(j=0;j<num[i];j++)
			if(!(num[i+1]==6&&j=2))
				ans+=f[i][j];
		if(num[i]==4||(num[i+1]==6&&num[i]=2)) break;
	}
	return res;
}

int main()
{
	int i;
	int n,m;
	initDp();
	while(scanf("%d%d",&n,&m)&&n&&m)
		printf("%d\n",solve(m+1)-solve(n));
	return 0;
}
