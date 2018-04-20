#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>

typedef long long ll;

const int P=1e9+7;

ll f[64][2];

int num[64],len;

ll dfs(int lv,int la,bool lim)
{
	if(!lv) return 1;
	ll &f=::f[lv][la];
	if(!lim&&~f) return f;
	ll res=0;
	int n= lim?num[lv]:1;
	for(int i=0;i<=n;i++)
	{
		if(i&&la) continue;
		res+=dfs(lv-1,i,lim&&i==n);
	}
	if(!lim) f=res;
	return res;
}

inline ll calc(ll x)
{
	for(len=0;x;x>>=1) num[++len]=x&1;
	return dfs(len,0,1);
}

struct Mt
{
	int m00,m01,m10,m11;
	Mt(bool ty=0){m00=m11=ty,m10=m01=0;}
	Mt(int a,int b,int c,int d):m00(a),m01(b),m10(c),m11(d){}
};
inline Mt operator *(const Mt &a,const Mt &b)
{
	Mt res;
	res.m00=((ll)a.m00*b.m00+(ll)a.m01*b.m10)%P;
	res.m01=((ll)a.m00*b.m10+(ll)a.m10*b.m11)%P;
	res.m10=((ll)a.m01*b.m00+(ll)a.m11*b.m01)%P;
	res.m11=((ll)a.m01*b.m10+(ll)a.m11*b.m11)%P;
	return res;
} 

inline Mt qpow(Mt a,ll x)
{
	Mt res(1);
	for(;x;x>>=1,a=a*a)
		if(x&1) res=res*a;
	return res;
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		memset(f,-1,sizeof f);
		ll x;scanf("%lld",&x);
		printf("%lld\n",calc(x)-1);
		Mt ans(1,1,1,0);
		ans=qpow(ans,x+1);
		printf("%d\n",ans.m00);
	}
	return 0;
}
/*
3
123
34231412412
3124235432154352
*/
