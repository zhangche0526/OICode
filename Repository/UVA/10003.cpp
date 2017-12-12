#include<iostream>
#include<cstdio>

const int MAXN=1005,INF=1e9;

int n,L,c[MAXN];
int f[MAXN][MAXN],pos[60][60];

int main()
{
	int i,l,len,r,mid;
	for(i=1;i<=55;i++) pos[i-1][i]=i;
	while(~scanf("%d",&L)&&L)
	{
		scanf("%d",&n);
		for(i=1;i<=n;i++) scanf("%d",c+i);
		c[0]=0,c[n+1]=L;
		for(len=2;len<=n+1;len++)
			for(l=0,r=l+len;r<=n+1;l++,r++)
			{
				f[l][r]=INF;
				for(mid=pos[l][r-1];mid<=pos[l+1][r];mid++)
				{
					int tmp=f[l][mid]+f[mid][r];
					if(tmp<f[l][r]) f[l][r]=tmp,pos[l][r]=mid;
				}
				f[l][r]+=c[r]-c[l];
			}
		printf("The minimum cutting is %d.\n",f[0][n+1]);
	}
	return 0;
}
