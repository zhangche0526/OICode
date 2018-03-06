#include<iostream>
#include<cstdio>
using std::min;
typedef long long ll;

const int MAXN=5e4+5;

int pri[MAXN<<3],pcnt;bool notPri[MAXN];
int musum[MAXN];
inline void preTab()
{
	int i,j;
	musum[1]=1;
	for(i=2;i<MAXN;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i,musum[i]=-1;
		for(j=1;j<=pcnt&&i*pri[j]<MAXN;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j]) musum[i*pri[j]]=-musum[i];
			else {musum[i*pri[j]]=0;break;}
		}
	}
	for(i=2;i<MAXN;i++) musum[i]+=musum[i-1];
}

int k;
inline ll calc(int n,int m)
{
	n/=k,m/=k;
	int l,r;ll res=0;
	for(l=1;l<=min(n,m);l=r+1)
		r=min(n/(n/l),m/(m/l)),
		res+=(ll)(n/l)*(m/l)*(musum[r]-musum[l-1]);
	return res;
}

inline ll solve(int a,int b,int c,int d)
{
	return calc(b,d)-calc(b,c-1)-calc(a-1,d)+calc(a-1,c-1);
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int a,b,c,d;scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
		printf("%lld\n",solve(a,b,c,d));
	}
	return 0;
}

