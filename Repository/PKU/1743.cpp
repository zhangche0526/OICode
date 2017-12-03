#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=2e4+5;

int sa[MAXN];
int t1[MAXN],t2[MAXN],c[MAXN];
int isSim(int *na,int o,int la,int len)
{return na[o]==na[la]&&na[o+len]==na[la+len];}
void buildSA(int *na,int n,int m)
{
	int i,j,p,*x=t1,*y=t2;
	for(i=0;i<m;i++) c[i]=0;
	for(i=0;i<n;i++) c[x[i]=na[i]]++;
	for(i=1;i<m;i++) c[i]+=c[i-1];
	for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
	for(j=1,p=1;p<n;j<<=1,m=p)
	{
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[y[i]]]++;
		for(i=1;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1,x[sa[0]]=0;
		for(i=1;i<n;i++)
			x[sa[i]]=isSim(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
int rk[MAXN],ht[MAXN];
void calHt(int *na,int n)
{
	int i,j,k=0;
	for(i=1;i<=n;i++) rk[sa[i]]=i;
	for(i=0;i<n;i++)
	{
		if(k) k--;
		j=sa[rk[i]-1];
		while(na[i+k]==na[j+k]) k++;
		ht[rk[i]]=k;
	}
}

bool check(int n,int k)
{
	int i,l=sa[1],r=sa[1];
	for(i=2;i<=n;i++)
	{
		if(ht[i]<k) l=r=sa[i];
		else
		{
			l=min(l,sa[i]),r=max(r,sa[i]);
			if(r-l+1>=k) return true;
		}
	}
	return false;
}

int na[MAXN];
int main()
{
	int n,i,la,rc;
	while(scanf("%d",&n)&&n)
	{
		n--;
		scanf("%d",&la);
		for(i=0;i<n;i++)
		{
			scanf("%d",&rc);
			na[i]=rc-la+100;
			la=rc;
		}
		na[n]=0;
		buildSA(na,n+1,200);
		calHt(na,n);
		int l=1,r=n>>1,mid;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(n,mid)) l=mid+1;
			else r=mid-1;
		}
		int ans=r+1;
		printf("%d\n",ans>=5?ans:0);
	}
}
