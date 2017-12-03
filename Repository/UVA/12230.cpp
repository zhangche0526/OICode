#include<iostream>
#include<cstdio>

const int MAXN=1e3+5;

int L[MAXN],v[MAXN];

int main()
{
	int Case=0,n,D;
	while(scanf("%d%d",&n,&D)&&(n||D))
	{
		int i,p;double ans=D;
		for(i=1;i<=n;i++) scanf("%d%d%d",&p,L+i,v+i);
		for(i=1;i<=n;i++) ans+=2.0*L[i]/v[i]-L[i];
		printf("Case %d: %.3f\n\n",++Case,ans);
	}
	return 0;
}
