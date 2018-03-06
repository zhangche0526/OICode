#include<iostream>
#include<cstdio>
using std::min;
typedef long long ll;

const int MAXN=1e7+5;

int pri[MAXN],pcnt;bool notPri[MAXN];
int v[MAXN],a[MAXN],k[MAXN];
int gsum[MAXN];
inline void preTab()
{
	int i,j;
	for(i=2;i<MAXN;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i,a[i]=k[i]=1;
		for(j=1;j<=pcnt&&i*pri[j]<MAXN;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j])
			{
				if(!v[i]||v[i]==a[i]) v[i*pri[j]]=a[i];
				else v[i*pri[j]]=-1;
				a[i*pri[j]]=1,k[i*pri[j]]=k[i]+1;
			}
			else
			{
				v[i*pri[j]]=v[i],a[i*pri[j]]=a[i]+1,k[i*pri[j]]=k[i];
				break;
			}
		}
		if(v[i]&&v[i]!=a[i]) gsum[i]=gsum[i-1];
		else gsum[i]=gsum[i-1]+(k[i]&1 ? 1:-1);
	}
}

inline ll solve(int n,int m)
{
	ll res = 0;
	int l,r;
	for(l=r=1;l<=n&&l<=m;l=r+1)
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
		printf("%lld\n",solve(n,m));
	}
	return 0;
}
