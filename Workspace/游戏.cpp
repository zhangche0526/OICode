#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=1005;

int pri[MAXN],pcnt;bool notPri[MAXN];
inline void preTab(int n)
{
	int i,j;
	for(i=2;i<=n;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i;
		for(j=1;j<=pcnt&&i*pri[j]<=n;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j]==0) break;
		}
	}
}

int n;
ll f[MAXN][MAXN];
int main()
{
	int i,j,k;scanf("%d",&n);
	preTab(n);
	f[0][0]=1;
	for(i=1;i<=pcnt;i++)
	{
		for(j=0;j<=n;j++) f[i][j]=f[i-1][j];
		for(j=pri[i];j<=n;j*=pri[i])
			for(k=0;j+k<=n;k++)
				f[i][j+k]+=f[i-1][k];
	}
	ll ans=0;
	for(i=0;i<=n;i++) ans+=f[pcnt][i];
	printf("%lld",ans);
	return 0;
}
