#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=100;
struct ST
{
	int f[MAXN][32];
	void init(int * na,int len)
	{
		int i,k;
		for(i=1;i<=len;i++) f[i][0]=na[i];
		for(k=1;(1<<k)<=len;k++)
			for(i=1;i+(1<<k)-1<=len;i++)
				f[i][k]=min(f[i][k-1],f[i+(1<<(k-1))][k-1]);
	}
	int calRMQ(int l, int r)
	{
		int k=log(r-l+1)/log(2);
		return min(f[l][k],f[r+1-(1<<k)][k]);
	}
} st;
