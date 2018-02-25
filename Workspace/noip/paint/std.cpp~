#include<iostream>
#include<cstdio>

const int MAXN=1005;

int n,m,k;
int f[MAXN][MAXN],g[MAXN][MAXN];

inline void paintBlk(int x1,int y1,int x2,int y2)
{f[x1][y1]++,f[x2+1][y1]--,f[x1][y2+1]--,f[x2+1][y2+1]++;}

inline void paintLne(int x1,int y1,int x2,int y2)
{
	if(x1+y1==x2+y2)
		for(;x1<=x2;x1++,y1--)
			g[x1][y1]++;
	else
		for(;x1<=x2;x1++,y1++)
			g[x1][y1]++;
}

inline void calSufSum()
{
	int i,j;
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
		f[i][j]+=f[i][j-1];
	for(j=1;j<=m;j++) for(i=1;i<=n;i++)
		f[i][j]+=f[i-1][j];
}

int main()
{
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
	int i,j;scanf("%d%d%d",&n,&m,&k);
	while(k--)
	{
		int t,x1,y1,x2,y2;scanf("%d%d%d%d%d",&t,&x1,&y1,&x2,&y2);
		if(t) paintBlk(x1,y1,x2,y2);
		else paintLne(x1,y1,x2,y2);
	}
	calSufSum();
	for(i=1;i<=n;i++) for(j=1;j<=m;j++)
		printf("%d%c",f[i][j]+g[i][j]," \n"[j==m]);
	return 0;
}
