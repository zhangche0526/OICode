#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int dis[101][101];
bool check[101];
int casecnt=0;
int main()
{
	int u,v;
	while(scanf("%d%d",&u,&v)&&u)
	{
		int sum=0;
		int i,j,k;
		int N=0;
		memset(dis,63,sizeof(dis));
		memset(check,false,sizeof(check));
		do 
		{
			dis[u][v]=1;
			if(!check[u]) ++N,check[u]=true;
			if(!check[v]) ++N,check[v]=true;
		}
		while(scanf("%d%d",&u,&v)&&u);
		for(i=1;i<=100;i++) dis[i][i]=0;
		for(k=1;k<=100;k++)
			for(i=1;i<=100;i++)
				for(j=1;j<=100;j++)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		for(i=1;i<=100;i++)
			for(j=1;j<=100;j++)
				if(dis[i][j]<(int)1e9)
					sum+=dis[i][j];
		double ans=(double)sum/(N*(N-1));
		printf("Case %d: average length between pages = %.3lf clicks\n",++casecnt,ans);
	}
	return 0;
}
