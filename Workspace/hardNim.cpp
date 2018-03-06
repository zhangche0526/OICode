#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;

const int MAXM=5e4+5,P=1e9+7,REV2=500000004;
int qpow(int a,int x)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%P)
		if(x&1) res=(ll)res*a%P;
	return res;
}

int pri[MAXM>>3],pcnt;bool notPri[MAXM];
inline void preTab()
{
	int i,j;
	for(i=2;i<MAXM;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i;
		for(j=1;j<=pcnt&&i*pri[j]<MAXM;j++)
		{
			notPri[i*pri[j]]=true;
			if(!(i%pri[j])) break;
		}
	}
}

void FWT(int *a,int n,bool rev)
{
	int i,j,k;
	for(i=1;i<n;i<<=1)
		for(j=0;j<n;j+=i<<1)
			for(k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				if(rev) a[j+k]=(ll)(x+y)*REV2%P,a[i+j+k]=(ll)(x+P-y)*REV2%P;
				else a[j+k]=(x+y)%P,a[i+j+k]=(x+P-y)%P;
			}
}

int n,m;
int a[1<<16];
int main()
{
	preTab();
	while(~scanf("%d%d",&n,&m))
	{
		int i,L=1;while(L<=m) L<<=1;
		memset(a,0,sizeof a);
		for(i=1;i<=pcnt&&pri[i]<=m;i++) a[pri[i]]=1;
		FWT(a,L,false);
		for(i=0;i<L;i++) a[i]=qpow(a[i],n);
		FWT(a,L,true);
		printf("%d\n",a[0]);
	}
}
