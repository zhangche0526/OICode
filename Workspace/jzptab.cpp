#include<iostream>
#include<cstdio>
typedef long long ll;
using std::min;
const int MAXN=1e7+5,P=1e8+9;

inline int add(int a,int b){return (a+b)%P;}
inline void uadd(int &a,int b){a=add(a,b);}
inline int mns(int a,int b){return (a-b+P)%P;}
inline int mul(int a,int b){return (ll)a*b%P;}

bool notPri[MAXN];
int pri[MAXN],pcnt,sum[MAXN];
inline void preTab()
{
	int i,j;
	sum[1]=1;
	for(i=2;i<MAXN;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i,sum[i]=mul(i,mns(1,i));
		for(j=1;j<=pcnt&&i*pri[j]<MAXN;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j]) sum[i*pri[j]]=mul(sum[i],sum[pri[j]]);
			else {sum[i*pri[j]]=mul(sum[i],pri[j]);break;}
		}
	}
	for(i=2;i<MAXN;i++) sum[i]=(sum[i]+sum[i-1])%P;
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

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,m;scanf("%d%d",&n,&m);
		printf("%d\n",f(n,m));
	}
	return 0;
}
