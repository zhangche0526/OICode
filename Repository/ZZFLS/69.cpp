#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int L=51;
ll a[L+1];
ll n;

void insert(ll x)
{
	int i,j;
	for(i=L;i>=0;i--)
	{
		if(!(x&(1LL<<i))) continue;
		if(a[i]) x^=a[i];
		else 
		{
			for(j=0;j<i;j++)
				if(x&(1LL<<j)) x^=a[j];
			for(j=i+1;j<=L;j++)
				if(a[j]&(1LL<<i)) a[j]^=x;
			a[i]=x;
			return;
		}
	}
}

ll calMax()
{
	ll res=0;
	for(int i=0;i<=L;i++)
		res^=a[i];
	return res;
}

int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		ll x;scanf("%lld",&x);
		insert(x);
	}
	printf("%lld",calMax());
	return 0;
}
