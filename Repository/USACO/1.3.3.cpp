/*
ID:zhangch33
LANG:C++
TASK:crypt1
*/
#include<iostream>
#include<cstdio>
using namespace std;

bool hash[10000];
int num[10];
int N;

int mypow(int x,int y)
{
	int res=1;
	while(y--) res*=x;
	return res;
}

inline void initHash()
{
	int i,j,k;
	for(k=2;k<=4;k++)
		for(i=0;i<=10000;i++)
		{
			int res=0,x=i;
			for(j=1;j<=mypow(10,k-1);j*=10)
				res+=num[x%N]*j,x/=N;
			hash[res]=true;
		}
}

int main()
{
	freopen("crypt1.in","r",stdin);
	freopen("crypt1.out","w",stdout);
	int i,j;
	scanf("%d",&N);
	for(i=0;i<N;i++) scanf("%d",&num[i]);
	///
	initHash();
	///
	int a,b;
	int ans=0;
	for(a=100;a<=999;a++)
	{
		if(!hash[a]) continue;
		for(b=10;b<=99;b++)
		{
			if(!hash[b]) continue;
			int c=a*(b%10),d=a*(b/10),e=a*b;
			if(c>999||c<99) continue;
			if(!hash[c]) continue;
			if(d>999||d<99) continue;
			if(!hash[d]) continue;
			if(e>9999||e<999) continue;
			if(!hash[e]) continue;
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
