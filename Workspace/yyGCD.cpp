#include<iostream>
#include<cstdio>
using std::min;
typedef long long ll;

const int MAXN=1e7+5;

int pri[MAXN<<3],pcnt;bool notPri[MAXN];
int mu[MAXN],gsum[MAXN];

inline void preTab()
{
	int i,j;
	for(i=2;i<MAXN;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i,mu[i]=-1,gsum[i]=1;
		for(j=1;j<=pcnt&&i*pri[j]<MAXN;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j]) mu[i*pri[j]]=-mu[i],gsum[i*pri[j]]=mu[i]-gsum[i];
			else {mu[i*pri[j]]=0,gsum[i*pri[j]]=mu[i];break;}
		}
	}
	for(i=2;i<MAXN;i++) gsum[i]+=gsum[i-1];
}

inline ll calc(int n,int m)
{
	int l,r;ll res=0;
	for(l=1;l<=min(n,m);l=r+1)
		r=min(n/(n/l),m/(m/l)),
		res+=(ll)(n/l)*(m/l)*(gsum[r]-gsum[l-1]);
	return res;
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,m;scanf("%d%d",&n,&m);
		printf("%lld\n",calc(n,m));
	}
	return 0;
}
