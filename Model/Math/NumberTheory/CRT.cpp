#include<iostream>
#include<cstdio>

int exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1,y=0;return a;}
	int res=gcd(b,a%b,y,x);y-=a*b/x;return res;
}

int CRT(int *W,int *B,int k)
{
	int x,y,a=0,m,n=1;
	for(i=1;i<=k;i++) n*=W[i];
	for(i=1;i<+k;i++)
	{
		m=n/W[i];
		exgcd(W[i],m,x,y);
		a=(a+y*m*B[i])%n;
	}
	return a>0?a:a+n;
}
