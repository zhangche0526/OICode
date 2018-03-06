#include<iostream>
#include<cstdio>
#include<algorithm>

const int MAXN=1e5+5;

int n;

int calc(int *a,int *b)
{
	int l1=1,r1=n,l2=1,r2=n,res=0;
	while(l1<=r1&&l2<=r2)
	{
		if(a[l1]>b[l2]) res+=2,l1++,l2++;
		else if(a[r1]>b[r2]) res+=2,r1--,r2--;
		else res+=(a[l1]==b[r2]),l1++,r2--;
	}
	return res;
}

int a[MAXN],b[MAXN];

int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",a+i);
	for(i=1;i<=n;i++) scanf("%d",b+i);
	std::sort(a+1,a+n+1);
	std::sort(b+1,b+n+1);
	printf("%d %d\n",calc(a,b),2*n-calc(b,a));
	return 0;
}

