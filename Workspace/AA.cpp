#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
const int MAXN=1005,P=1e9+7;

int qpow(int a,int x)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%P)
		if(x&1) res=(ll)res*a%P;
	return res;
}

int k,Pa,Pb;

int f[MAXN][MAXN];

int dfs(int a,int ab)
{
	if(ab>=k) return ab;
	if(a==k) return ((ll)Pa*qpow(Pb,P-2)%P+ab+k)%P;
	int &f=::f[a][ab];
	if(~f) return f;
	return f=((ll)Pa*dfs(a+1,ab)%P+(ll)Pb*dfs(a,ab+a)%P)%P;
}

int main()
{
	scanf("%d%d%d",&k,&Pa,&Pb);
	int sum=(Pa+Pb)%P;
	Pa=(ll)Pa*qpow(sum,P-2)%P;
	Pb=(ll)Pb*qpow(sum,P-2)%P;
	memset(f,-1,sizeof f);
	printf("%d",dfs(1,0));
	return 0;
}
