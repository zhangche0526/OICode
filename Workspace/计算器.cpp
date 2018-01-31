#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using std::ceil;
using std::sqrt;
typedef long long ll;

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
	mp.clear();
	int i,sp=ceil(sqrt(p));
	int aB=1;mp[aB]=0;
	int aspInv=qpow(qpow(a,sp,p),p-2,p);
	for(i=1;i<sp;i++)
	{
		aB=(ll)aB*a%p;
		if(!mp.count(aB)) mp[aB]=i;
	}
	for(i=0;i<=sp;i++)
	{
		if(mp.count(b)) return i*sp+mp[b];
		b=(ll)b*aspInv%p;
	}
	return -1;
}

int main()
{
	int T,K;scanf("%d%d",&T,&K);
	while(T--)
	{
		int a,b,p,ans;scanf("%d%d%d",&a,&b,&p);
		a%=p;
		switch(K)
		{
			case 1:printf("%d\n",qpow(a,b,p));break;
			case 2:
				   b%=p;
				   if(!a&&b) puts("Orz, I cannot find x!");
				   else printf("%d\n",int((ll)b*qpow(a,p-2,p)%p));
				   break;
			case 3:
				   b%=p;
				   if(~(ans=BSGS(a,b,p))) printf("%d\n",ans);
				   else puts("Orz, I cannot find x!");
				   break;
		}
	}
	return 0;
}
