#include<iostream>
#include<cstdio>
#include<map>
#include<cmath>
using std::ceil;
using std::sqrt;
typedef long long ll;

int gcd(int a,int b){return b?gcd(b,a%b):a;}
void exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1,y=0;return;}
	exgcd(b,a%b,y,x);y-=x*(a/b);
}
int inv(int a,int p){int x,y;exgcd(a,p,x,y);return (x%p+p)%p;}

int qpow(int a,int x,int p)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%p)
		if(x&1) res=(ll)res*a%p;
	return res;
}

std::map<int,int> mp;
int BSGS(int a,int b,int p)
{
	if(!a) return b?-1:1;
	a%=p,b%=p;
	int cnt=0;
	for(int g=gcd(a,p);g>1;g=gcd(a,p))
	{
		if(b%g) return -1;
		b/=g,p/=g;b=(ll)b*inv(a/g,p)%p;
		cnt++;
		if(b==1) return cnt;
	}
	if(p==1) return cnt;

	mp.clear();
	int i,sp=ceil(sqrt(p));
	int aB=1;mp[aB]=0;
	int aspInv=inv(qpow(a,sp,p),p);
	for(i=1;i<sp;i++)
	{
		aB=(ll)aB*a%p;
		if(!mp.count(aB)) mp[aB]=i;
	}
	for(i=0;i<=sp;i++)
	{
		if(mp.count(b)) return i*sp+mp[b]+cnt;
		b=(ll)b*aspInv%p;
	}
	return -1;
}

int main()
{
	int a,b,p,ans;
	while(scanf("%d%d%d",&a,&p,&b)&&p)
	{
		if(~(ans=BSGS(a,b,p))) printf("%d\n",ans);
		else puts("No Solution");
	}
	return 0;
}
