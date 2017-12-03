#include<iostream>
#include<cstdio>
typedef long long ll;

int n,m;
int cnt[520];
ll f[15][105][520];
bool ok1[520],ok2[520][520];

inline void initOK()
{
	int i,j;
	for(i=0;i<(1<<n);i++)
		if((i&(i>>1))==0)
		{
			int x,t=0;
			for(x=i;x;x>>=1) t+=(x&1);
			cnt[i]=t;ok1[i]=true;
		}
	for(i=0;i<(1<<n);i++) if(ok1[i])
		for(j=0;j<(1<<n);j++) if(ok1[2])
			if((i&j)==0&&(i&(j>>1))==0&&(j&(i>>1))==0)
				ok2[i][j]=true;
}

int main()
{
	int i,j,k,t;
	scanf("%d%d",&n,&m);
	initOK();
	for(i=0;i<(1<<n);i++) if(ok1[i]) f[1][cnt[i]][i]=1;
	for(k=1;k<n;k++)
		for(i=0;i<(1<<n);i++) if(ok1[i])
			for(j=0;j<(1<<n);j++) if(ok1[j])
				if(ok2[i][j])
					for(t=cnt[i];t+cnt[j]<=m;t++)
						f[k+1][t+cnt[j]][j]+=f[k][t][i];
	ll ans=0;
	for(i=0;i<(1<<n);i++) ans+=f[n][m][i];
	printf("%lld\n",ans);
	return 0;
}
