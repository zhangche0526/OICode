#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=1e5+5;

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
char s1[MAXN],s2[MAXN];
int na[MAXN<<<1];
int main()
{
	int i,mid,n;
	scanf("%s%s",s1,s2);
	mid=strlen(s1);n=strlen(s2)+mid+1;
	for(i=0;i<mid;i++) na[i]=s1[i];na[mid]=1;
	for(i=mid+1;i<n;i++) na[i]=s2[n-(mid+1)];na[n]=0;
	buildSA(na,n+1,256);
	calHeight(na,n);
	int ans=0;
	for(i=2;i<=n;i++)
		if((sa[i]<mid&&mid<sa[i-1])||(sa[i-1]<mid&&mid<sa[i]))
			ans=max(ans,ht[i]);
	printf("%d\n",ans);
}
