#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=50,MAXT=200,INF = 1000000000;
int dp[MAXT+1][MAXN+1];
bool ht[MAXT+1][MAXN+1][2];
int t[MAXN+1];
int casecnt;
int main()
{
	int N,T,M1,M2;
	while(scanf("%d%d",&N,&T)&&N)
	{
		int i,j,x;
		for(i=1;i<N;i++) scanf("%d",&t[i]);

		memset(ht,false,sizeof(ht));
		scanf("%d",&M1);
		while(M1--)
		{
			scanf("%d",&x);
			for(j=1;j<N;j++)
			{
				if(x>T) break;
				ht[x][j][0]=true;x+=t[j];
			}
					
		}
		scanf("%d",&M2);
		while(M2--)
		{
			scanf("%d",&x);
			for(j=N-1;j>=1;j--) 
			{
				if(x>T) break;
				ht[x][j+1][1]=true;x+=t[j];
			}
				
		}
		for(int i = 1; i < N; i++) dp[T][i] = INF;
		dp[T][N]=0;
		for(i=T-1;i>=0;i--)
			for(j=1;j<=N;j++)
			{
				dp[i][j]=dp[i+1][j]+1;
				if(j<N && i+t[j]<=T && ht[i][j][0])
					dp[i][j]=min(dp[i][j],dp[i+t[j]][j+1]);
				if(j>1 && i+t[j-1]<=T && ht[i][j][1])
					dp[i][j]=min(dp[i][j],dp[i+t[j-1]][j-1]);
			}
		printf("Case Number %d: ",++casecnt);
		if(dp[0][1]<(int)1e9) printf("%d\n",dp[0][1]);
		else printf("impossible\n");
	}
	return 0;
}
