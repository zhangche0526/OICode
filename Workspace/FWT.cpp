#include<iostream>
#include<cstdio>

void FWT(int *a,int n,bool rev)
{
	int i,j,k;
	for(i=1;i<n;i<<=1)
		for(j=0;j<n;j+=i<<1)
			for(k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				if(rev) a[j+k]=(x+y)/2,a[i+j+k]=(x-y)/2;
				else a[j+k]=x+y,a[i+j+k]=x-y;
			}
}
