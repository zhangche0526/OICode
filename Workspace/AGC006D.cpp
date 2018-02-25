#include<iostream>
#include<cstdio>

const int MAXN=1e5+5;

int n;
int a[MAXN<<1];
bool jud(int k)
{
	for(int i=0;i<n;i++)
	{
		if(a[n+i]<k&&a[n+i+1]<k) return false;
		if(a[n-i]<k&&a[n-i-1]<k) return false;
		if(a[n+i]>=k&&a[n+i+1]>=k) return true;
		if(a[n-i]>=k&&a[n-i-1]>=k) return true;
	}
	return a[1]>=k;
}

int main()
{
	int i;scanf("%d",&n);
	for(i=1;i<n<<1;i++) scanf("%d",a+i);
	int l=0,r=n<<1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(jud(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d",r);
	return 0;
}
