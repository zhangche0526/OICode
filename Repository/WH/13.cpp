#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAXN=40000;
struct tree{int l,r,lc,rc;ll a[2][2],mx;}tr[MAXN+1];
int tlen;
ll mymax(ll x,ll y){return (x>y)?x:y;}
void bt(int l,int r)
{
	tlen++;int now=tlen;
	tr[now].l=l;tr[now].r=r;
	tr[now].lc=tr[now].rc=-1;
	memset(tr[now].a,0,sizeof(tr[now].a));
	tr[now].mx=0;
	if(l<r)
	{
		int mid=(l+r)>>1;
		tr[now].lc=tlen+1;bt(l,mid);
		tr[now].rc=tlen+1;bt(mid+1,r);
	}
}
void updata(int now,int lc,int rc)
{
	tr[now].a[0][0]=mymax(tr[lc].a[0][1]+tr[rc].a[0][0],tr[lc].a[0][0]+tr[rc].a[1][0]);
	tr[now].a[1][0]=mymax(tr[lc].a[1][1]+tr[rc].a[0][0],tr[lc].a[1][0]+tr[rc].a[1][0]);
	tr[now].a[0][1]=mymax(tr[lc].a[0][1]+tr[rc].a[0][1],tr[lc].a[0][0]+tr[rc].a[1][1]);
	tr[now].a[1][1]=mymax(tr[lc].a[1][1]+tr[rc].a[0][1],tr[lc].a[1][0]+tr[rc].a[1][1]);	
}
void change(int now,int x,ll k)
{
	if(tr[now].l==tr[now].r)
	{
		tr[now].a[1][1]=k;
		tr[now].mx=k;
		return;
	}
	int mid=(tr[now].l+tr[now].r)>>1,lc=tr[now].lc,rc=tr[now].rc;
	if (x<=mid) change(lc,x,k);
	else change(rc,x,k);
	updata(now,lc,rc);
	tr[now].mx=mymax(tr[now].a[0][0],tr[now].a[0][1]);
	tr[now].mx=mymax(tr[now].mx,mymax(tr[now].a[1][0],tr[now].a[1][1]));
}
int main()
{
	ios::sync_with_stdio(false);
	freopen("13.in","r",stdin);
	freopen("13.out","w",stdout);
	int n,q,i;ll ans,x,c;
	cin>>n>>q;
	tlen=0;
	bt(1,n);
	for(i=1;i<=n;i++)
	{
		cin>>x;
		change(1,i,x);
	}
	ans=0;
	while(q--)
	{
		cin>>x>>c;
		change(1,x,c);
		ans+=tr[1].mx;
	}
	cout<<ans<<endl;
	return 0;
}
