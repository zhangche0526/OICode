/*
TASK:pprime
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

int a,b;

bool isPri(int x)
{
	if(x==1) return false;
	int i;
	bool res=true;
	for(i=2;i<=sqrt(x);i++)
		if(x%i==0)
		{
			res=false;
			break;
		}
	return res;
}

int l,num[10];

void initPal(int x)
{
	int i,j,k;
	if(x==l/2+1)
	{
		if(l%2)
		{
			for(k=0;k<=9;k++)
			{
				int res=0;
				for(i=1,j=1;i<=x-1;i++,j*=10)
					res+=num[i]*j;
				res+=k*j;
				for(i=x-1,j*=10;i>=1;i--,j*=10)
					res+=num[i]*j;
				if(res>=a&&res<=b)
					if(isPri(res)) 
						printf("%d\n",res);
			}
		}else 
		{
			int res=0;
			for(i=1,j=1;i<=x-1;i++,j*=10)
				res+=num[i]*j;
			for(i=x-1;i>=1;i--,j*=10)
				res+=num[i]*j;
			if(res>=a&&res<=b)
					if(isPri(res)) 
						printf("%d\n",res);
		}
	}
	else for(i=0;i<=9;i++)
	{
		num[x]=i;
		initPal(x+1);
	}
}

int main()
{
	freopen("pprime.in","r",stdin);
	freopen("pprime.out","w",stdout);
	int i;
	scanf("%d%d",&a,&b);
	for(i=1;i<=8;i++)
	{
		l=i;
		initPal(1);
	}
	return 0;
}
