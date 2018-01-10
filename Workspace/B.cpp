#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
typedef long long ll;
const int P=998244353;

ll n;int lgn;

struct S{ll x,y;S(ll x=0,ll y=0):x(x),y(y){}};
S operator +(S a,S b)
{
	if(a.x>b.x) return a;
	if(a.x<b.x) return b;
	return S(a.x,(a.y+b.y)%P);
}
S operator *(S a,S b){return S(a.x+b.x,a.y*b.y%P);}
struct P{S s0,s1;P(){}P(S s0,S s1):s0(s0),s1(s1){}};

std::map<ll,P> f;

P dp(ll l,ll r)
{
	ll len=r-l+1;
	if(f.count(len)) return f[len];
	if(l==r) return f[len]=P(S(0,1),S(-1,0));
	ll mid=(l+r)>>1;
	P l=dp(l,mid),r=dp(mid+1,r);
	S s0=(l.s0+l.s1)*(r.s0+r.s1),
	  s1=(l.s0*(r.s0+r.s1))+(r.s0*(l.s0+l.s1));
	if(s1.x>=0) s1.x++;
	return f[len]=P(s0,s1);
}

int main()
{
	scanf("%lld",&n);
	P ans=dp(1,n);ans.s0=ans.s0+ans.s1;
	printf("%lld %lld",ans.s0.x,ans.s0.y);
	return 0;
}
