#include<iostream>
#include<cstdio>
typedef long long ll;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}

const int MAXN=1e5+5;
const double eps=1e-6,INF=1e13;

int N,K;
int op,ed;

int na[MAXN];
double sum[MAXN];
inline bool chk(double x)
{
	double mnv=INF;int i,mnp=0;sum[0]=0;
	for(i=1;i<=N;i++) sum[i]=sum[i-1]+(double)na[i]-x;
	for(i=K;i<=N;i++)
	{
		if(sum[i-K]<mnv) mnv=sum[i-K],mnp=i-K;
		if(sum[i]-mnv>=0) {op=mnp+1,ed=i;return true;}
	}
	return false;
}

int main()
{
	int i;
	scanf("%d%d",&N,&K);
	for(i=1;i<=N;i++) scanf("%d",na+i);
	double l=-INF,r=INF;
	while(r-l>eps)
	{
		double mid=(l+r)/2;
		if(chk(mid)) l=mid;
		else r=mid;
	}
	ll p=0,q=ed-op+1;
	for(i=op;i<=ed;i++) p+=na[i];
	int g=gcd(p,q);p/=g,q/=g;
	if(q<0) p*=-1,q*=-1;
	printf("%lld/%lld",p,q);
	return 0;
}
