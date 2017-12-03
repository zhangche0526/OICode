#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
 
using namespace std;
 
const int N=755,mod=1000000007;
int n,m,k;
int f[N][N],mp[N][N];
 
int sumc[N*N],sum;
void solve(int l,int r)
{
	if(l==r)return ;
	int mid=(l+r)/2;
	solve(l,mid);
	for(int j=1;j<m;++j)
	{
		for(int i=l;i<=mid;++i)
			sum=(sum+f[i][j])%mod,
			sumc[mp[i][j]]=(sumc[mp[i][j]]+f[i][j])%mod;
		for(int i=mid+1;i<=r;++i)
			f[i][j+1]=((f[i][j+1]+sum)%mod+mod-sumc[mp[i][j+1]])%mod;
	}
	for(int j=1;j<m;++j)
		for(int i=l;i<=mid;++i)
			sumc[mp[i][j]]=0;
	sum=0;
	solve(mid+1,r);
}
 
int main()
{
	freopen("hopscotch.in","r",stdin);
	freopen("hopscotch.out","w",stdout);
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			scanf("%d",&mp[i][j]);
	f[1][1]=1;
	solve(1,n);
	printf("%d",f[n][m]);
	return 0;
}
