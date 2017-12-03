#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=1e6+5,MAXM=1e3+5;

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

int rmq[MAXN];
inline void calRMQ(int n)
{
	int i,mid=rk[0];
	for(i=mid-1;i>=1;i--) 
		rmq[i]=i==mid-1?ht[mid]:min(rmq[i+1],ht[i+1]);
	for(i=mid+1;i<=n;i++) 
		rmq[i]=i==mid+1?ht[mid]:min(rmq[i-1],ht[i-1]);
}

char s[MAXN];
int na[MAXN];
int main()
{
	freopen("data.in","r",stdin);
	while(~scanf("%s",s))
	{
		if(s[0]=='.') break;
		int i,k,len=strlen(s);
		for(i=0;i<len;i++) na[i]=s[i];
		na[len]=0;
		buildSA(na,len+1,256);
		calHt(na,len);
		calRMQ(len);
		for(k=1;k<=len;k++)
			if(len%k==0)
				if(rmq[rk[k]]==len-k)
				{
					printf("%d\n",len/k);
					break;
				}
	}
	return 0;
}
