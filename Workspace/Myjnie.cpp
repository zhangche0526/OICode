#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

const int MAXN=55,MAXM=4005;

int n,m;

int a[MAXM],b[MAXM],c[MAXM];int val[MAXM],gcnt;

int p[MAXN][MAXN][MAXM],K[MAXN][MAXN][MAXM];
int f[MAXN][MAXN][MAXM];

void DP()
{
	int i,j,k;
	for(int len=1;len<=n;len++)
	for(int l=1,r=len;r<=n;l++,r++)
	{
		static int g[MAXN][MAXM];memset(g,0,sizeof g);
		for(k=1;k<=m;k++) if(l<=a[k]&&b[k]<=r) for(i=a[k];i<=b[k];i++) g[i][c[k]]++;
		for(i=l;i<=r;i++) for(j=m-1;j;j--) g[i][j]+=g[i][j+1];
		for(k=m;k;k--)
		{
			int mxv=0;
			for(i=l;i<=r;i++)
			{
				int tmp=f[l][i-1][k]+f[i+1][r][k]+val[k]*g[i][k];
				if(tmp>=mxv) mxv=tmp,p[l][r][k]=i;
			}
			if(mxv>=f[l][r][k+1]) f[l][r][k]=mxv,K[l][r][k]=k;
			else f[l][r][k]=f[l][r][k+1],K[l][r][k]=K[l][r][k+1];
		}
	}
}

int ans[MAXN];
void dfs(int l,int r,int k)
{
	if(l>r) return;
	int mid=p[l][r][k=K[l][r][k]];
	ans[mid]=val[k];
	dfs(l,mid-1,k);
	dfs(mid+1,r,k);
}

int main()
{
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) scanf("%d%d%d",a+i,b+i,c+i),val[i]=c[i];
	std::sort(val+1,val+m+1);gcnt=std::unique(val+1,val+m+1)-(val+1);
	for(i=1;i<=m;i++) c[i]=std::lower_bound(val+1,val+gcnt+1,c[i])-val;
	DP();
	printf("%d\n",f[1][n][1]);
	dfs(1,n,1);
	for(i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
/*
7 5
1 4 7
3 7 13
5 6 9
6 7 1
1 2 5
*/
