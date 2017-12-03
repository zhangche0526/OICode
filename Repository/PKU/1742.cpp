#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=105,MAXM=1e5+5;

int N,M;
int A[MAXN],C[MAXN],p[MAXM];
bool ok[MAXM];

int main()
{
	while(scanf("%d%d",&N,&M)!=EOF&&(N||M))
	{
		int i,j;
		std::memset(ok,false,sizeof(ok));
		for(i=1;i<=N;i++) scanf("%d",&A[i]);
		for(i=1;i<=N;i++) scanf("%d",&C[i]);
		ok[0]=true;
		for(i=1;i<=N;i++)
		{
			memset(p,0,sizeof(p));
			for(j=1;j<=M;j++)
			{
				if(ok[j]||j<A[i]) continue;
				if(ok[j-A[i]]&&p[j-A[i]]<C[i])
					ok[j]=true,p[j]=p[j-A[i]]+1;
			}
		}
		int ans=0;
		for(i=1;i<=M;i++) if(ok[i]) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
