#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=10,P=1e9+7;

int n;
int mp[MAXN];
int f[MAXN][2000],ans[MAXN],szPrd[MAXN];

int U;
inline void solve()
{ 
	int i;memset(ans,0,sizeof ans);
	ans[0]=0;ans[1]=1;ans[n+1]=U;
	for(int sz=2;sz<=n;sz++)
	{
		szPrd[0]=1;for(i=1;i<=n;i++) szPrd[i]=szPrd[i-1]*sz;
		memset(f,0,sizeof f);f[0][0]=1;
		for(i=0;i<n;i++)
			for(int S=0;S<1<<sz;S++) if(f[i][S])
				for(int k=0;k<1<<n;k++) if(!(mp[i+1]&k))
				{
					int nxt=0;
					for(int tmp=k,j=1;j+sz-1<=n;j++,tmp>>=1)
					{
						int now=(((tmp&((1<<sz)-1))==(1<<sz)-1)?(S/szPrd[j-1]%sz+1):0); 
						if(now>=sz){ nxt=-1; break; }
						nxt+=now*szPrd[j-1];
					}
					if(~nxt) f[i+1][nxt]=(f[i+1][nxt]+f[i][S])%P;
				}
		for(int S=0;S<1<<sz;S++) ans[sz]=(ans[sz]+f[n][S])%P;
	}
	for(i=0;i<=n;i++) printf("%d\n",((ans[i+1]-ans[i])%P+P)%P);
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i,j;scanf("%d",&n);
		memset(mp,0,sizeof mp);U=1;
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			{
				char c;
				do c=getchar();while(c!='o'&&c!='*');
				if(c=='o') (U<<=1)%=P;
				else mp[i]|=1<<j-1;
			}
		solve();
	}
	return 0;
}

