#include<iostream>
#include<cstdio>
typedef long long ll;
using std::min;
const int MAXN=1e7+5,P=20101009,I4=15075757;

bool notPri[MAXN];
int pri[MAXN],pcnt,sum[MAXN];
inline void preTab(int n)
{
	int i,j;
	sum[1]=1;
	for(i=2;i<=n;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i,sum[i]=-1;
		for(j=1;j<=pcnt&&i*pri[j]<=n;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j]) sum[i*pri[j]]=-sum[i];
			else {sum[i*pri[j]]=0;break;}
		}
	}
	for(i=1;i<=n;i++) sum[i]=(ll)sum[i]*i*i%P;
	for(i=2;i<=n;i++) sum[i]=(sum[i]+sum[i-1])%P;
}

inline int h(int x){return (ll)x*(x+1)/2%P;}
inline int g(int x,int y){return (ll)h(x)*h(y)%P;}
inline int f(int n,int m)
{
	int l,r,res=0;
	for(l=1;l<=min(n,m);l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		res=(res+(ll)(sum[r]-sum[l-1]+P)%P*g(n/l,m/l)%P)%P;
	}
	return res;
}
inline int calc(int n,int m)
{
	int l,r,res=0;
	for(l=1;l<=min(n,m);l=r+1)
	{
		r=min(n/(n/l),m/(m/l));
		res=(res+(ll)(l+r)*(r-l+1)/2%P*f(n/l,m/l)%P)%P;
	}
	return res;
}

int main()
{
	int n,m;scanf("%d%d",&n,&m);
	preTab(min(n,m));
	printf("%d",calc(n,m));
	return 0;
}
