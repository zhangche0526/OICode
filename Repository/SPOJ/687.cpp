#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

const int MAXN=5e4+5,MAXM=300;

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

int na[MAXN];
int main()
{
	int T,n;scanf("%d",&T);
	while(T--)
	{
		int i,j,k;char c;
		scanf("%d",&n);
		for(i=0;i<n;i++) 
		{do c=getchar();while(c==' '||c=='\n');na[i]=c;}
		na[n]=0;
		buildSA(na,n+1,256);
		calHt(na,n);
		st.init(ht,n);
		int ans=0,rans;
		for(i=1;i<n;i++)//len
			for(j=0;j+i<n;j+=i)//pos
			{
				k=calLCP(j,j+i);
				rans=k/i;
				int lpos=j-(i-k%i);
				if(lpos>=0)
					if(calLCP(lpos,lpos+i)>=i-k%i) rans++;
				if(rans>ans) ans=rans;
			}
		printf("%d\n",ans+1);
	}
}
