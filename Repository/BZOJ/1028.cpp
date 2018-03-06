#include<iostream>
#include<cstdio>

const int MAXN=405;

int n,m;

int cnt[MAXN],f[MAXN];

bool jud()
{
	int i,j;
	for(i=1;i<=n;i++)
		if(cnt[i]>=2)
		{
			bool ok=true;
			cnt[i]-=2;
			for(j=1;j<=n+2;j++) f[j]=cnt[j];
			for(j=1;j<=n+2;j++)
			{
				if(f[j]<0) {ok=false;break;}
				f[j]%=3;
				f[j+1]-=f[j];
				f[j+2]-=f[j];
			}
			cnt[i]+=2;
			if(ok) return true;
		}
	return false;
}

int ans[MAXN],acnt;
int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m*3+1;i++)
	{
		int x;scanf("%d",&x);
		cnt[x]++;
	}
	bool ok=false;
	for(i=1;i<=n;i++)
	{
		cnt[i]++;
		if(jud()) {ok=true;ans[++acnt]=i;}
		cnt[i]--;
	}
	for(i=1;i<=acnt;i++) 
	{
		printf("%d",ans[i]);
		if(i!=acnt) printf(" ");
	}
	if(!ok) puts("NO");
	return 0;
}
