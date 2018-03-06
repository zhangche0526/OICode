#include<iostream>
#include<cstdio>
#include<cstring>

int na[15],cnt[51],f[1030][1030];
char s[15];

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		memset(cnt,0,sizeof(cnt));
		memset(f,0,sizeof(f));
		int i,j,k;
		scanf("%s",s);
		int d;scanf("%d",&d);
		int len=strlen(s);
		for(i=0;i<len;i++)
			na[i]=s[i]-'0',++cnt[na[i]];
		f[0][0]=1;
		for(i=0;i<(1<<len);i++)
			for(j=0;j<d;j++)
				for(k=0;k<len;k++)
					if((i&(1<<k))==0)
						f[i|(1<<k)][(j*10+na[k])%d]+=f[i][j];
		int ans=f[(1<<len)-1][0];
		for(i=0;i<=9;i++)
			for(j=1;j<=cnt[i];j++)
				ans/=j;
		printf("%d\n",ans);
	}
	return 0;
}

