#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
const int MAXN=105;

char s[MAXN];

bool jud(int l1,int r1,int l2,int r2)
{
	if((r1-l1+1)%(r2-l2+1)) return false;
	for(int i=l1;i<=r1;i++)
		if(s[i]!=s[(i-l1)%(r2-l2+1)+l2]) return false;
	return true;
}

int calL(int x){int res=0;while(x) x/=10,res++;return res;}

bool vis[MAXN][MAXN];
int f[MAXN][MAXN];
int dp(int l,int r)
{
	if(l==r) return 1;
	if(vis[l][r]) return f[l][r];
	vis[l][r]=1;
	int res=r-l+1;
	for(int i=l;i<r;i++)
	{
		res=min(res,dp(l,i)+dp(i+1,r));
		if(jud(i+1,r,l,i))
			res=min(res,dp(l,i)+2+calL((r-i)/(i-l+1)+1));
	}
	return f[l][r]=res;
}

int main()
{
	scanf("%s",s+1);
	int n=strlen(s+1);
	int ans=dp(1,n);
	printf("%d",ans);
	return 0;
}
