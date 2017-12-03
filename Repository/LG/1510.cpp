#include<iostream>
#include<cstdio>
using namespace std;

int v,n,c;
int k[10001],m[10001];
int dp[100001]
int main()
{
	cin>>v>>n>>c;
	for(int i=1;i<=n;i++) cin>>k[i]>>m[i];
	for(int i=1;i<=n;i++)
		for(int j=v;j>=m[i];j--)
			dp[j]=max(dp[j],dp[j-m[i]]+k[i]);
	return 0;
}

