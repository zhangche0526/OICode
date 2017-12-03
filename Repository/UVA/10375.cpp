#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>

const int MAXN=1e4,MAXP=2e3+5;

int pri[MAXP],pcnt;bool notPri[MAXN+5];
inline void initPri()
{
	int i,j;
	for(i=2;i<=MAXN;i++)
	{
		if(!notPri[i]) pri[++pcnt]=i;
		for(j=1;j<=pcnt&&i*pri[j]<=MAXN;j++)
		{
			notPri[i*pri[j]]=true;
			if(i%pri[j]==0) break;
		}
	}
}

int idx[MAXP];
void addIdx(int x,int d)
{
	for(int i=1;i<=pcnt;i++)
		while(x%pri[i]==0)
			x/=pri[i],idx[i]+=d;
}
void addFac(int x,int d){for(int i=1;i<=x;i++) addIdx(i,d);}

int main()
{
	initPri();
	int i,p,q,r,s;
	while(~scanf("%d%d%d%d",&p,&q,&r,&s))
	{
		memset(idx,0,sizeof(idx));
		addFac(p,1);addFac(p-q,-1);addFac(q,-1);
		addFac(r,-1);addFac(r-s,1);addFac(s,1);
		double ans=1;
		for(i=1;i<=pcnt;i++) ans*=std::pow(pri[i],idx[i]);
		printf("%.5f\n",ans);
	}
	return 0;
}
