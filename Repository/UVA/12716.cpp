#include<iostream>
#include<cstdio>

const int MAXN=3e7;

int ans[MAXN+5];

inline void preTab()
{
	int i,a,c;
	for(c=1;c<=MAXN;c++)
		for(a=c*2;a<=MAXN;a+=c)
			if(c==(a^(a-c))) ans[a]++;
	for(i=1;i<=MAXN;i++) ans[i]+=ans[i-1];
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	for(int Case=1;Case<=T;Case++)
	{
		int N;
		scanf("%d",&N);
		printf("Case %d: %d\n",Case,ans[N]);
	}
	return 0;
}
