#include<cstdio>
#include<vector>
using namespace std;
typedef long long ll;

const int MAXN=51,MAXL=50;

class LB
{
private:
	ll a[MAXL];
	void ist(ll x)
	{
		int i,j;
		for(i=MAXL-1;i>=0;i--)
		{
			if(!(x&(1LL<<i))) continue;
			if(a[i]) x^=a[i];
			else
			{
				for(j=0;j<i;j++) if(x&(1LL<<j))	x^=a[j];
				for(j=i+1;j<MAXL;j++) if(a[j]&(1LL<<i)) a[j]^=x;
				a[i]^=x;
				return;
			}
		}
	}
public:
	ll calMxXor()
	{
		ll res=0;
		for(int i=0;i<MAXL;i++) res^=a[i];
		return res;
	}
	LB(ll *S,int n){for(int i=1;i<=n;i++) ist(S[i]);}
};

int n;
ll S[MAXN];

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%lld",S+i);
	static LB lb(S,n);
	printf("%lld",lb.calMxXor());
}
