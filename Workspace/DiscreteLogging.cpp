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
	int a,b,p,ans;
	while(~scanf("%d%d%d",&p,&a,&b))	
	{
		if(~(ans=BSGS(a,b,p))) printf("%d\n",ans);
		else puts("no solution");
	}
	return 0;
}
