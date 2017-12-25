#include<iostream>
#include<cstdio>
typedef long long ll;

const int MAXN=1e5+5,MAXM=2e5+5,P=1e9+7;

int qpow(int a,int x)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%P)
		if(x&1) res=(ll)res*a%P;
	return res;
}

int n,m,k;

int a[MAXN],d[MAXN];
int main()
{
	int i;scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	for(i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		d[u]++,d[v]++;
	}
	int ans=0;
	for(i=1;i<=n;i++) ans=(ans+(ll)a[i]*d[i]%P)%P;
	ans=(ll)ans*qpow(2*m,P-2)%P*k%P;
	printf("%d",ans);
	return 0;
}
