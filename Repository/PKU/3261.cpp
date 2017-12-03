#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=2e4+5,MAXM=1e6+5;

int N,K;

int sa[MAXN];
int t1[MAXN],t2[MAXN],c[MAXM];
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
bool check(int x,int n)
{
    int i,cnt=1;
    for(i=1;i<=n;i++)
	    if(ht[i]>=x)
	    {
			cnt++;
		    if(cnt>=K) return true;
	    }
    	else cnt=1;
    return false;
}
int na[MAXN];
int main()
{
	int i;
	scanf("%d%d",&N,&K);
	for(i=0;i<N;i++) scanf("%d",&na[i]),na[i]++;
	na[N]=0;
	buildSA(na,N+1,MAXM);
	calHt(na,N);
	int l=1,r=N,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid,N)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
	return 0;
}
