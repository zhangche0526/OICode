#include<iostream>
#include<cstdio>
#define bmv(x) (1<<(x-1))
const int MAXN=11,MAXM=1005,P=998244353;

inline void add(int &a,int b){a=(a+b%P)%P;}

int n,m;bool modd;

int f[MAXM][bmv(MAXN)][3][3],g[MAXN][MAXM];

char s[MAXM];
int main()
{
	int i,j,a,b;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(j=1;j<=m;j++) if(s[j]=='1') g[i][j]=1;
	}
	if(m&1) modd=true;
	else
	{
		m>>=1;
		for(i=1;i<=n;i++) for(j=1;j<=m;j++)
			g[i][j]|=g[i][j+m]<<1;
	}
	
	for(i=1;i<=n;i++)
	{
		if(g[i][1]&1) f[1][bmv(i)][0][0]=1;
		if(g[i][1]&2) f[1][bmv(i)][1][1]=1;
	}
	f[1][0][2][2]=1;
	for(i=2;i<=m;i++) for(int S=0;S<1<<n;S++)
	{
		int (&la)[3][3]=f[i-1][S];
		for(j=1;j<=n;j++) if(!(S&bmv(j)))
		{
			int (&o)[3][3]=f[i][S|bmv(j)];
			if(g[j][i]&1) for(a=0;a<=2;a++)
				add(o[a][0],la[a][1]+la[a][2]);
			if(g[j][i]&2) for(a=0;a<=2;a++)
				add(o[a][1],la[a][0]+la[a][2]);
		}
		int (&o)[3][3]=f[i][S];
		for(a=0;a<=2;a++) for(b=0;b<=2;b++)
			add(o[a][2],la[a][b]);
	}
	int (&o)[3][3]=f[m][(1<<n)-1],ans=0;
	add(ans,o[0][modd]+o[0][2]);add(ans,o[1][modd^1]+o[1][2]);
	for(b=0;b<=2;b++) add(ans,o[2][b]);
	printf("%d\n",ans);
	return 0;
}
