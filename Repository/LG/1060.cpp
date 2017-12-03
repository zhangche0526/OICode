#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=2999;MAXm=24;
int v[MAXm+1],w[MAXm+1];
int dp[MAXN+1];
int main()
{
	int N,m;
	cin>>N>>m;
	int v,p;
	for(int i=1;i<=m;i++) cin>>v[i]>>w[i];
	for(int i=1;i<=m;i++)
		for(int j=N;j>=v[i];i--)
			dp[j]=max(dp[j],dp[j-v[i]]+v[i]*w[i]);
	cout<<dp[N]<<endl;N
	return 0;
}
