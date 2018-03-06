#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
const int MAXN=1005,MAXL=63;

class LB
{
private:
	ll a[MAXL];
public:
	bool ist(ll x)
	{
		int i,j;
		for(i=MAXL-1;~i;i--)
		{
			if(!(x&(1LL<<i))) continue;
			if(a[i]) x^=a[i];
			else
			{
				for(j=0;j<i;j++) if(x&(1LL<<j)) x^=a[i];
				for(j=i+1;j<MAXL;j++) if(a[j]&(1LL<<i)) a[j]^=x;
				a[i]^=x;
				return true;
			}
		}
		return false;
	}
};

int n;
int stding[MAXN];
ll a[MAXN];int v[MAXN];
bool cmp(const int &x,const int &y){return v[x]>v[y];}

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%lld%d",a+i,v+i),stding[i]=i;
	std::sort(stding+1,stding+n+1,cmp);
	static LB lb;
	int ans=0;
	for(i=1;i<=n;i++)
		if(lb.ist(a[stding[i]]))
			ans+=v[stding[i]];
	printf("%d",ans);
	return 0;
}
