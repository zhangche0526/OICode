#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
inline void umx(int &a,int b){a=max(a,b);}

const int MAXN=20,MAXS=1<<15,P=1e9+7;
const char GN[]="AGCT";

int n,m;
char s[MAXN];

int trans[MAXS][4],f[2][MAXS];
inline void preDP()
{
	memset(trans,0,sizeof trans);
	int i;static int g[MAXN],h[MAXN];
	for(int S=0;S<1<<n;S++)
	{
		for(i=0;i<n;i++) h[i+1]=h[i]+bool((S>>i)&1);
		for(int c=0;c<4;c++)
		{
			for(i=1;i<=n;i++)
			{
				g[i]=max(g[i-1],h[i]);
				if(GN[c]==s[i]) umx(g[i],h[i-1]+1);
			}
			for(i=0;i<n;i++) if(g[i+1]-g[i]) trans[S][c]|=1<<i;
		}
	}
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i;
		scanf("%s",s+1);n=strlen(s+1);
		scanf("%d",&m);
		preDP();
		static int ans[MAXN],f[2][MAXS];
		memset(ans,0,sizeof ans);memset(f,0,sizeof f);
		int p=0;f[0][0]=1;
		for(i=1;i<=m;i++,p^=1)
		{
			memset(f[p^1],0,sizeof f[p^1]);
			for(int S=0;S<1<<n;S++)
				for(int c=0;c<4;c++)
					(f[p^1][trans[S][c]]+=f[p][S])%=P;
		}
		for(int S=0;S<1<<n;S++) (ans[__builtin_popcount(S)]+=f[p][S])%=P;
		for(i=0;i<=n;i++) printf("%d\n",ans[i]);
	}
	return 0;
}
