#include<iostream>
#include<cstdio>
#include<cmath>
typedef long long ll;

int divAll(int &x,int d)
{
	int res=1;
	while(x%d==0) x/=d,res*=d;
	return res;
}

ll solve(int n)
{
	if(n==1) return 2;
	int m=std::ceil(std::sqrt(n));
	ll ans=0;
	int cnt=0;
	for(int i=2;i<=m;i++)
		if(n%i==0) cnt++,ans+=divAll(n,i);
	if(n>1) cnt++,ans+=n;
	if(cnt<=1) ans++;
	return ans;
}

int main()
{
	int i;
	int n,Case=0;
	while(~scanf("%d",&n)&&n)
		printf("Case %d: %lld\n",++Case,solve(n)); 
	return 0;
}
