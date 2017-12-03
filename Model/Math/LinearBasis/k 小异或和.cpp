#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=55;

int n,m;

ll LB[MAXN];
ll LBSeq[MAXN];int scnt;

void insert(ll x)
{
	int i,j;
    for(i=MAXN-1;i>=0;--i)
    {
        if((x&(1LL<<i))==0) continue;
        if(LB[i]) x^=LB[i];
        else
        {
            for(j=0;j<i;++j)
            {
                if(x&(1LL<<j))
                    x^=LB[j];
            }
            for(j=i+1;j<MAXN;++j)
            {
                if(LB[j]&(1LL<<i))
                    LB[j]^=x;
            }
            LB[i]^=x;
            return;
        }
    }
}

ll qry(ll x)
{
    ll res=0;
    for(int i=1;i<=scnt;i++)
    {
        if(x&(1LL<<(i-1)))
            res^=LBSeq[i];
    }
    return res;
}

int main()
{
	int i;
    scanf("%d",&n);
    ll x;
    for(i=1;i<=n;i++)
		scanf("%lld",&x),insert(x);
    for(i=0;i<MAXN;i++)
		if(LB[i]) LBSeq[++scnt]=LB[i];
    scanf("%d",&m);
    while(m--)
    {
        scanf("%lld",&x);
        if(scnt!=n) --x;
        if(x>=(1LL<<scnt)) printf("-1\n");
        else printf("%lld\n",qry(x));
    }
    return 0;
}
