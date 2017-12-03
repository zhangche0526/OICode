#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long ll;
const int MAXN=1e5;
struct node{ll id,x,ls;double y;}ss[MAXN];
ll r[MAXN],V[MAXN];
ll N,L,C,i,ans;
ll lowbit(ll x){return x&(-x);}
void ins(ll x,ll y) {for(;x<=N;x+=lowbit(x)) r[x]+=y;}
ll ask(ll x){ll res=0;for(;x>0;x-=lowbit(x)) res+=r[x];return res;}
bool cmp1(node x,node y) {return x.y<y.y;}
bool cmp2(node x,node y) {return x.id<y.id;}
int main()
{
	ios::sync_with_stdio(false);
	freopen("12.in","r",stdin);
	freopen("12.out","w",stdout);
	cin>>N>>L>>C;
	for(i=1;i<=N;i++) cin>>V[i];
	sort(V+1,V+1+N);ans=0;
	memset(r,0,sizeof(r));
	for(i=1;i<=N;i++)
	{
		double orz=1.0*L*V[i]/V[N];
		ss[i].y=(double)(orz-(L*V[i]/V[N]));
		ss[i].x=orz-ss[i].y;
		ss[i].id=i;
		ans+=(i-1)*ss[i].x-ask(i);
		ins(i,ss[i].x);
	}
	sort(ss+1,ss+1+N,cmp1);
	ll p=1;ss[1].ls=1;
	for(i=2;i<=N;i++)
		if(abs(ss[i].y-ss[i-1].y)<0.000001) ss[i].ls=p;
		else ss[i].ls=p++;
	sort(ss+1,ss+1+N,cmp2);
	memset(r,0,sizeof(r));
	for(i=1;i<=N;i++)
	{
		ans-=(i-1)-ask(ss[i].ls);
		ins(ss[i].ls,1);
	}
	cout<<ans<<endl;
	return 0;
}
