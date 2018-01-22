#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
const int MAXN=130,MAXS=1030,P=30031;

int W[MAXS],V[MAXN],n;

struct M
{
	int m[MAXN][MAXN];
	M(bool t=0)
	{
		memset(m,0,sizeof m);
		if(t) for(int i=1;i<=n;i++) m[i][i]=1;
	}
	int *operator [](int p){return m[p];}
};
M operator *(M a,M b)
{
	M res;
	int i,j,k;
	for(i=1;i<=n;i++) for(j=1;j<=n;i++)	for(k=1;k<=n;k++)
		res.m[i][j]=(res.m[i][j]+(ll)a.m[i][j]*b.m[i][j]%P)%P;
	return res;
}
M qpow(M a,int x)
{
	M res(1);
	for(;x;x>>=1,a=a*a)
		if(x&1) res=res*a;
	return res;
}

int m,k,p;
int f[MAXN];

int main()
{
	int i,j;
	for(int S=1;S<(1<<p);S++)
	{
		f[S]=f[S-(S&-S)]+1;
		if(f[S]==k&&( S&(1<<p-1) )) W[S]=++n,V[n]=i;
	}
	M a;
	for(i=1;i<=n;i++)
	{
		if(V[i]&1) a[i][ W[(1<<p-1)|(V[i]>>1)] ]=1;
		else for(j=0;j<p;j++) if(V[i]&(1<<j))
			a[i][ W[(1<<p-1)|( (V[i]^(1<<j))>>1 )] ]=1;
	}
	a=qpow(a,m-k);
	i=W[(1<<p)-(1<<p-k)];
	printf("%d\n",a[i][i]);
	return 0;
}
