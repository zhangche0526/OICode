#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
typedef long long ll;

const int MAXN=50001;

int sa[MAXN],t1[MAXN],t2[MAXN],c[MAXN];
inline bool isSim(int *na,int o,int la,int len)
{return na[o]==na[la]&&na[o+len]==na[la+len];}
void buildSA(int *na,int n,int m)
{
	int i,j,p,*x=t1,*y=t2;
	memset(c,0,sizeof(c));
	for(i=0;i<n;i++) c[x[i]=na[i]]++;
	for(i=1;i<m;i++) c[i]+=c[i-1];
	for(i=n-1;i>=0;i--) sa[--c[x[i]]]=i;
	for(j=p=1;p<n;j<<=1,m=p)
	{
		for(i=n-j,p=0;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]-j>=0) y[p++]=sa[i]-j;
		memset(c,0,sizeof(c));
		for(i=0;i<n;i++) c[x[y[i]]]++;
		for(i=1;i<m;i++) c[i]+=c[i-1];
		for(i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=1,x[sa[0]]=0;
		for(i=1;i<n;i++)
			x[sa[i]]=isSim(y,sa[i],sa[i-1],j)?p-1:p++;
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

char s[MAXN];
int na[MAXN];
int main()
{
	int i,n,T;
	ll ans;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",s);
		n=strlen(s);
		for(i=0;i<n;i++) na[i]=s[i];
		na[n]=0;
		buildSA(na,n+1,128);
		calHt(na,n);
		ans=(ll)n*(n+1)/2;
		for(i=1;i<=n;i++) ans-=ht[i];
		printf("%lld\n",ans);
	}
	return 0;
}
