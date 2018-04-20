#include<iostream>
#include<cstdio>
#include<cstring>
const int MAXN=1005;

int n,m,k;

struct Mt
{
	double a[MAXN];
	Mt(bool ty=0){a[0]=ty;for(int i=1;i<n;i++) a[i]=.0;}
};

Mt operator *(const Mt &a,const Mt &b)
{
	Mt res;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			res.a[(i+j)%n]+=a.a[i]*b.a[j];
	return res;
}

Mt qpow(Mt a,int x)
{
	Mt res(1);
	for(;x;x>>=1,a=a*a)
		if(x&1) res=res*a;
	return res;
}

int main()
{
	int i;scanf("%d%d%d",&n,&m,&k);
	Mt ans;
	for(i=1;i<=n;i++) scanf("%lf",&ans.a[i-1]);
	Mt mt;mt.a[0]=1.0-1.0/m,mt.a[1]=1.0/m;
	ans=ans*qpow(mt,k);
	for(i=1;i<=n;i++) printf("%.3lf\n",ans.a[i-1]);
	return 0;
}
/*
5 20 11
3 7 2 1 5
*/
