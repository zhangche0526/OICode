/*
TASK:numtri
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#define max(a,b) (a>b?a:b)
using namespace std;

int R;
const int MAXR=1000,INF=~0U>>1;
int tree[MAXR+1][MAXR+1];
int dp[MAXR+1][MAXR+1];

int main()
{
	freopen("numtri.in","r",stdin);
	freopen("numtri.out","w",stdout);
	int i,j;
	scanf("%d",&R);
	for(i=1;i<=R;i++)
		for(j=1;j<=i;j++)
			scanf("%d",&tree[i][j]);
	for(i=1;i<=R;i++) dp[R][i]=tree[R][i];
	for(i=R-1;i>=1;i--)
		for(j=1;j<=i;j++)
			dp[i][j]=tree[i][j]+max(dp[i+1][j],dp[i+1][j+1]);
	printf("%d\n",dp[1][1]);
	return 0;
}
