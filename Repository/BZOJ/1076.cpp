#include<iostream>
#include<cstdio>

const int MAXK=105,MAXN=20;

int K,N;

double f[MAXK][65540];

int P[MAXN],preC[MAXN];

int main()
{
	int i,j,k,t;
	scanf("%d%d",&K,&N);
	for(i=1;i<=N;i++)
	{
		scanf("%d",P+i);
		do scanf("%d",&t),preC[i]+=t?(1<<(t-1)):0;
		while(t);
	}
	for(i=K;i;i--)
		for(j=0;j<(1<<N);j++)
		{
			for(k=1;k<=N;k++)
				if((preC[k]&j)==preC[k])
					f[i][j]+=std::max(f[i+1][j],f[i+1][j|(1<<k-1)]+P[k]);
				else f[i][j]+=f[i+1][j];
			f[i][j]/=N;
		}
	printf("%.6f\n",f[1][0]);
	return 0;
}
