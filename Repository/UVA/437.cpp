#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=35;

int n;
int blk[MAXN][3],f[MAXN][3];

void getD(int *a,int x,int y)
{
	int cnt=0;
	for(int i=0;i<3;i++) 
		if(i!=y) a[cnt++]=blk[x][i];
}

int dp(int x,int y)
{
	if(f[x][y]>0) return f[x][y];
	int i,j,u[2],v[2];
	getD(u,x,y);
	for(i=1;i<=n;i++)
		for(j=0;j<3;j++)
		{
			getD(v,i,j);
			if(v[0]<u[0]&&v[1]<u[1])
				f[x][y]=std::max(f[x][y],dp(i,j));
		}
	f[x][y]+=blk[x][y];
	return f[x][y];
}

int main()
{
	int T=0;
	while(~scanf("%d",&n)&&n)
	{
		int i,j;
		for(i=1;i<=n;i++)
		{
			for(j=0;j<3;j++)
				scanf("%d",&blk[i][j]);
			std::sort(blk[i],blk[i]+3);
		}
		memset(f,0,sizeof(f));
		int ans=0;
		for(i=1;i<=n;i++)
			for(j=0;j<3;j++)
				ans=std::max(ans,dp(i,j));
		printf("Case %d: maximum height = %d\n",++T,ans);
	}
	return 0;
}
