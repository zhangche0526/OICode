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
