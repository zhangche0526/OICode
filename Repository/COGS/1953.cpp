#include<iostream>
#include<cstdio>

const int MAXN=755,P=1e9+7;

int R,C,K;
int mp[MAXN][MAXN],sum,clrsum[MAXN*MAXN],f[MAXN][MAXN];

void solve(int l,int r)
{
	if(l==r) return;
	int i,j,mid=(l+r)>>1;
	solve(l,mid);
	for(j=1;j<C;j++)
	{
		for(i=l;i<=mid;i++)
			sum=(sum+f[i][j])%P,
			clrsum[mp[i][j]]=(clrsum[mp[i][j]]+f[i][j])%P;
		for(i=mid+1;i<=r;i++)
			f[i][j+1]=((f[i][j+1]+sum)%P+P-clrsum[mp[i][j+1]])%P;
	}
	for(j=1;j<C;j++)
		for(i=l;i<=mid;i++)
			clrsum[mp[i][j]]=0;
	sum=0;
	solve(mid+1,r);
}

int main()
{
	freopen("hopscotch.in","r",stdin);
	freopen("hopscotch.out","w",stdout);
	int i,j;
	scanf("%d%d%d",&R,&C,&K);
	for(i=1;i<=R;i++)
		for(j=1;j<=C;j++)
			scanf("%d",&mp[i][j]);
	f[1][1]=1;
	solve(1,R);
	printf("%d\n",f[R][C]);
	return 0;
}
