#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;

const int MAXN=2e3+2;

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
struct ST
{
	int f[MAXN][32];
	void init(int * na,int len)
	{
		int i,k;
		for(i=1;i<=len;i++) f[i][0]=na[i];
		for(k=1;(1<<k)<=len;k++)
			for(i=1;i+(1<<k)-1<=len;i++)
				f[i][k]=min(f[i][k-1],f[i+(1<<(k-1))][k-1]);
	}
	int calRMQ(int l, int r)
	{
		int k=log(r-l+1)/log(2);
		return min(f[l][k],f[r+1-(1<<k)][k]);
	}
} st;

int calLCP(int x,int y)
{
	x=rk[x],y=rk[y];
	if(x>y) swap(x,y);
	return st.calRMQ(x+1,y);
}

char s[MAXN];int na[MAXN];
int main()
{
	int i,n,len,lcp,pos,maxLcp=0;
	scanf("%s",s);len=strlen(s);
	for(i=0;i<len;i++) na[i]=s[i]; 
	na[len]=1;
	for(i=0;i<len;i++) na[i+len+1]=s[len-i-1];
	n=len*2+1;na[n]=0;
	buildSA(na,n+1,256);
	calHt(na,n);
	st.init(ht,n);
	for(i=0;i<len;i++)
	{
		lcp=calLCP(i,n-i);
		if(lcp*2>maxLcp) maxLcp=lcp*2,pos=i-lcp;
		lcp=calLCP(i,n-i-1);
		if(lcp*2-1>maxLcp) maxLcp=lcp*2-1,pos=i-lcp+1;
	}
	s[pos+maxLcp]=0;
	printf("%s\n",s+pos);
	return 0;
}
