#include<algorithm>
#include<cstdio>
#include<iostream>
using namespace std;
const int INF=9999999;
typedef long long ll;
struct point{int x;long long v;}a[20001];
bool cmp(const point&X,const point&Y){return X.v<Y.v;}
int Min=INF,Max=-INF;
int L,R,o,n;
ll sum[200000],num[200000];
ll now,ans;
ll query(int root,int l,int r)
{
    	if(!num[root]) return 0;
    	if(L<=l&&r<=R) 
      		return  sum[root]-num[root]*now;
    	int mid=(l+r)>>1;
    	ll t=0;
    	if(mid>=L) t+=query(root<<1,l,mid);
    	if(mid<R)  t+=query(root<<1|1,mid+1,r);
    	return t;
}
void insert(int root,int l,int r,int p)
{
    	sum[root]+=p;
    	num[root]++;
    	if(l==r)  return ;
    	int mid=(l+r)>>1;
    	if(mid>=p) insert(root<<1,l,mid,p);
    	else insert(root<<1|1,mid+1,r,p);
}
int main()
{
	ios::sync_with_stdio(false);
	freopen("7.in","r",stdin);
	freopen("7.out","w",stdout);
    	cin>>n;
    	for(int i=1;i<=n;i++)
    	{
		cin>>a[i].v>>a[i].x;
      		Min=min(a[i].x,Min);
      		Max=max(a[i].x,Max);
    	}
    	sort(a+1,a+1+n,cmp);
    	for(int i=1;i<=n;i++)
    	{
        	now=a[i].x;
        	L=a[i].x,R=Max;
        	ans+=a[i].v*query(1,Min,Max);
        	L=Min,R=a[i].x;
        	ans-=a[i].v*query(1,Min,Max);
        	insert(1,Min,Max,a[i].x);
    	}
	cout<<ans<<endl;
}
