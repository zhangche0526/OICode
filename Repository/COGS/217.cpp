#include<iostream>
#include<cstdio>
using namespace std;

int N,D,K;

int f[1<<15+5];

int ill[1005];bool ok[1<<15+5];

int main()
{
	freopen("disease.in","r",stdin);
	freopen("disease.out","w",stdout);
	int i,j,x,y;scanf("%d%d%d",&N,&D,&K);
	for(i=1;i<=N;i++)
	{
		scanf("%d",&x);
		for(j=1;j<=x;j++)
		{
			scanf("%d",&y);
			ill[i]+=1<<(y-1);
		}
	}
	int tot=(1<<D)-1;
	for(i=0;i<=tot;i++)
	{
		int icnt=0;
		for(j=i;j;j>>=1)
			if(j&1) icnt++;
		if(icnt<=K) ok[i]=true;
	}
	for(i=1;i<=N;i++)
		for(j=tot;j>=0;j--)
			f[j|ill[i]]=max(f[j|ill[i]],f[j]+1);
	int ans=0;
	for(i=0;i<=tot;i++)
		if(ok[i]) ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}
