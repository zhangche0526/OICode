#include<iostream>
#include<cstdio>
#include<cmath>
using std::min;
typedef unsigned long long ull;

const int MAXN=1e5+5,SN=355;

int N,Q;
int bnum,bsz;

int a[MAXN];
ull sum1[SN],sum2[SN][SN];
void initA()
{
	int i,j;
	for(i=1;i<=bnum;i++)
	{
		int la=(i-1)*bsz;
		for(j=1;j<=bsz&&la+j<=N;j++) sum2[i][j]=sum2[i][j-1]+a[la+j];
		sum1[i+1]=sum1[i]+sum2[i][j-1];
	}
}
ull calSum(int x) {return sum1[(x-1)/bsz+1]+sum2[(x-1)/bsz+1][(x-1)%bsz+1];}
ull calSum(int l,int r){return calSum(r)-calSum(l-1);}

int fl[MAXN],fr[MAXN];
int cont[SN][MAXN];
ull sum[SN];
void initF()
{
	int i,j;
	for(i=1;i<=bnum;i++)
	{
		int la=(i-1)*bsz;
		for(j=1;j<=bsz&&la+j<=N;j++)
			sum[i]+=calSum(fl[la+j],fr[la+j]),
			cont[i][fl[la+j]]++,cont[i][fr[la+j]+1]--;
	}
	for(i=1;i<=bnum;i++)
		for(j=1;j<=N;j++) cont[i][j]+=cont[i][j-1];
}

void mdf(int p,int v)
{
	int i,pB=(p-1)/bsz+1;
	for(i=p;i<=pB*bsz&&i<=N;i++)
		sum2[pB][i-(pB-1)*bsz]+=v-a[p];
	for(i=pB+1;i<=bnum;i++) sum1[i]+=v-a[p];

	for(i=1;i<=bnum;i++) sum[i]+=(ull)(v-a[p])*cont[i][p];

	a[p]=v;
}
ull qry(int l,int r)
{
	int i,lB=(l-1)/bsz+1,rB=(r-1)/bsz+1;ull res=0;
	if(lB==rB) for(i=l;i<=r;i++) res+=calSum(fl[i],fr[i]);
	else
	{
		for(i=l;i<=lB*bsz;i++) res+=calSum(fl[i],fr[i]);
		for(i=lB+1;i<=rB-1;i++) res+=sum[i];
		for(i=(rB-1)*bsz+1;i<=r;i++) res+=calSum(fl[i],fr[i]);
	}
	return res;
}

int main()
{
	int i;
	scanf("%d",&N);
	bsz=std::sqrt(N);bnum=(N+bsz-1)/bsz;
	for(i=1;i<=N;i++) scanf("%d",a+i);initA();
	for(i=1;i<=N;i++) scanf("%d%d",fl+i,fr+i);initF();
	scanf("%d",&Q);
	while(Q--)
	{
		int opt;scanf("%d",&opt);
		int x,y;scanf("%d%d",&x,&y);
		if(opt==1) mdf(x,y);
		else printf("%llu\n",qry(x,y));
	}
	return 0;
}
