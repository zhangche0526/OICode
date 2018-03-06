#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
typedef long long ll;

const int MAXN=1e5+5,MAXL=51;

class LB
{
private:
	ll a[MAXL];
	ll spanSz;
	bool hasZero;
	std::vector<ll> vec;
	void ist(ll x)
	{
		int i,j;
		for(i=MAXL-1;i>=0;i--)
		{
			if(!(x&(1LL<<i))) continue;
			if(a[i]) x^=a[i];
			else
			{
				for(j=0;j<i;++j) if(x&(1LL<<j))	x^=a[j];
				for(j=i+1;j<MAXL;++j) if(a[j]&(1LL<<i)) a[j]^=x;
				a[i]^=x;
				return;
			}
		}
	}
public:
	ll calKMxXor(ll k)
	{
		if(hasZero) k--;
		if(k>spanSz) return -1;
		ll res=0;
		for(int i=0;i<vec.size();i++)
			if((k>>i)&1) res^=vec[i];
		return res;
	}
	LB(ll *S,int n)
	{
		int i;
		for(i=1;i<=n;i++) ist(S[i]);
		for(i=0;i<MAXL;i++) if(a[i])
			vec.push_back(a[i]);
		spanSz=(1LL<<vec.size())-1;
		if(n>vec.size()) hasZero=true;
		std::sort(vec.begin(),vec.end());
	}
};

int n,m;
ll S[MAXN];

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%lld",S+i);
	static LB lb(S,n);
	scanf("%d",&m);
	while(m--)
	{
		ll k;scanf("%lld",&k);
		printf("%lld\n",lb.calKMxXor(k));
	}
	return 0;
}
