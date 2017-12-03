/*
ID:zhangch33
TASK:hamming
LANG:C++
*/
#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=64;
int N,B,D;
int num[MAXN+1];

int calHam(int a,int b)
{
	int res=0;
	while(a||b)
	{
		if((a&1)^(b&1)) ++res;
		a>>=1,b>>=1;
	}return res;
}

int main()
{
	freopen("hamming.in","r",stdin);
	freopen("hamming.out","w",stdout);
	int i,j,k;
	scanf("%d%d%d",&N,&B,&D);
	int tmp=calHam(0,7);
	j=0;
	for(i=1;i<=N;i++)
		for(;j<(1<<B);j++)
		{
			bool ok=true;
			for(k=1;k<=i-1;k++)
				if(calHam(num[k],j)<D)
				{
					ok=false;
					break;
				}
			if(ok) 
			{
				num[i]=j;
				break;
			}
		}
	for(i=1;i<=N;i++)
	{
		if(i%10==0||i==N) printf("%d\n",num[i]);
		else printf("%d ",num[i]);
	}
	return 0;
}

