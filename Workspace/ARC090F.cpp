#include<iostream>
#include<cstdio>

int MAXN=1e7,MAXM=255e5;

int S

int f[MAXN];
inline void preTab()
{
	int i;
	for(int l=1,r=10,len=1;l<MAXN;l=r,r*=10,len++)
		for(i=1;i<=r;i++) f[i]=len;
	for(i=MAXN;i<=MAXM;i++) f[i]=8;
}

inline int cal1()
{
	int res=0,cnt=0;
	int l,r;
	for(l=1,r=0;l<MAXN&&r<MAXM;i++)
	{
		cnt-=f[i-1];
		while(cnt+f[r+1]<=S&&r<MAXM) cnt+=f[++r];
		if(cnt==S) ++res;
	}
	return res;
}

inline int cal2()
{
	int lim=S>>3,res=lim;
	for
}

int main()
{
	int i;scanf("%d",&S);

	return 0;
}
