#include<iostream>
#include<cstdio>
typedef long long ll;

const int MAXN=1e6+5;

char s[MAXN];
int next[MAXN],f[MAXN];
int main()
{
	int i,j,n;
	scanf("%d%s",&n,s);
	for(i=1;i<n;i++)
	{
		j=next[i];
		while(j&&s[i]!=s[j]) j=next[j];
		next[i+1]=(s[i]==s[j]?j+1:0);
	}
	ll ans=0;
	for(i=1;i<=n;i++)
	{
		if(next[i]) f[i]=f[next[i]];
		else f[i]=i;
		ans+=i-f[i];
	}
	printf("%lld",ans);
	return 0;
}
