#include<iostream>
#include<cstdio>
#include<algorithm>

const int MAXN=105,MAXM=15,INF=1<<30;

int M,N;

int mp[MAXM][MAXN],f[MAXM][MAXN],next[MAXM][MAXN];

int main()
{
	while(~scanf("%d%d",&M,&N))
	{
		int i,j,k,ans=INF,fir=1;
		for(i=1;i<=M;i++)
			for(j=1;j<=N;j++)
				scanf("%d",&mp[i][j]);
		for(j=N;j;j--)
			for(i=1;i<=M;i++)
			{
				if(j==N) f[i][j]=mp[i][j];
				else
				{
					int rows[3]={i,i-1,i+1};
					if(i==1) rows[1]=M;
					if(i==M) rows[2]=1;
					std::sort(rows,rows+3);
					f[i][j]=INF;
					for(k=0;k<3;k++)
					{
						int v=f[rows[k]][j+1]+mp[i][j];
						if(v<f[i][j]) f[i][j]=v,next[i][j]=rows[k];
					}
				}
				if(j==1&&f[i][j]<ans) {ans=f[i][j];fir=i;}
			}
		printf("%d",fir);
		for(i=next[fir][1],j=2;j<=N;i=next[i][j],j++)
			printf(" %d",i);
		printf("\n%d\n",ans);
	}
	return 0;
}
