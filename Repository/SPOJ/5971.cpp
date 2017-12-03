#include<iostream>
#include<cstdio>

typedef long long ll;

const int MAXN=1e6+5;

int n;
int phi[MAXN];
ll ans[MAXN];

inline void calPhi()
{
	int i,j;
	phi[1]=1;
	for(i=2;i<=(int)1e6;i++)
		if(!phi[i])
			for(j=i;j<=(int)1e6;j+=i)
			{
				if(!phi[j]) phi[j]=j;
				phi[j]=phi[j]/i*(i-1);
			}
}

inline void preTab()
{
	int i,j;
	ans[1]=1;
	for(i=2;i<=(int)1e6;i++)
	{
		ans[i]+=i;
		for(j=i;j<=(int)1e6;j+=i)
			ans[j]+=i*(ll)phi[i]/2*j;
	}
}

int main()
{
	calPhi();
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		printf("%lld\n",ans[n]);
	}
	return 0;
}
