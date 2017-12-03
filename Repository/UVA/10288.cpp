#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
typedef long long ll;

ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}

int calLen(ll a)
{
	int res=0;
	while(a) a/=10,res++;
	return res;
}

struct F
{
	ll a,b;
	void rdc(){ll tmp=gcd(a,b);a/=tmp,b/=tmp;}
	F(){a=0,b=1;}
	F(ll x){a=x,b=1;}
	F(ll x,ll y){a=x,b=y;rdc();}
	void print()
	{
		ll ext=a/b,newa=a%b;
		int i,extLen=calLen(ext),aLen=calLen(newa),bLen=calLen(b);
		if(newa)
		{
			for(i=1;i<=extLen+1;i++) putchar(' '); 
			printf("%lld\n",newa);
		}
		if(ext||!newa)
		{
			printf("%lld",ext);
			if(newa)
			{
				putchar(' ');
				for(i=1;i<=std::max(aLen,bLen);i++) putchar('-');
				putchar('\n');
			}else putchar('\n');
		}
		if(newa)
		{
			for(i=1;i<=extLen+1;i++) putchar(' '); 
			printf("%lld\n",b);
		}
	}
};

F operator +(F x,F y)
{
	F res;
	res.b=lcm(x.b,y.b);
	res.a=res.b/x.b*x.a+res.b/y.b*y.a;
	res.rdc();
	return res;
}
F operator *(F x,F y)
{
	F res=F(x.a*y.a,x.b*y.b);
	res.rdc();
	return res;
}

int n;

F dp[35][35];

int main()
{
	int i,j;
	for(i=1;i<=33;i++)
	{
		dp[i][0]=F(0);
		for(j=1;j<=i;j++)
			dp[i][j]=(dp[i][j-1]*F(j,i)+F(1))*F(i,j);
	}
	while(scanf("%d",&n)!=EOF)
		dp[n][n].print();
	return 0;
}
