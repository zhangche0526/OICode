#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN=55;

int n,m;

ll LB[MAXN];
ll LBSeq[MAXN];int scnt;

inline void insert(ll x)
{
    for(int i=MAXN-1;i>=0;--i)
    {
        if((x&(1LL<<i))==0) continue;
        if(LB[i]) x^=LB[i];
        else
        {
            for(int j=0;j<i;++j)
            {
                if(x&(1LL<<j))
                    x^=LB[j];
            }
            for(int j=i+1;j<MAXN;++j)
            {
                if(LB[j]&(1LL<<i))
                    LB[j]^=x;
            }
            LB[i]^=x;
            return;
        }
    }
}

int main()
{
    scanf("%d",&n);
    ll x;
    for(int i=1;i<=n;++i)
		scanf("%lld",&x),insert(x);
    ll res=0;
    for(int i=0;i<MAXN;++i)
		if(LB[i]) LBSeq[++scnt]=LB[i];
    for(int i=1;i<=scnt;i++) res^=LBSeq[i];
    printf("%lld\n",res);
    return 0;
}
