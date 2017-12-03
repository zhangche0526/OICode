/*
TASK:subset
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
int N;
ll dp[10000];

int main()
{
	freopen("subset.in","r",stdin);
	freopen("subset.out","w",stdout);
	int i,j;
	scanf("%d",&N);
	int sum=N*(N+1)/2;
	if(sum&1)
	{
		printf("0\n");
		return 0;
	}
	sum/=2;
	dp[0]=1;
	for(i=1;i<=N;i++)
		for(j=sum;j>=i;j--)
			dp[j]+=dp[j-i];
	printf("%lld\n",dp[sum]/2);
}
