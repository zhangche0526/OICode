/*
ID:zhangch33
TASK:skidesign
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN=1000,INF=~0U>>1;
int N;
int num[MAXN+1];

int cal(int l,int r)
{
	int res=0,i;
	for(i=1;i<=N;i++)
	{
		if(num[i]<l) res+=(l-num[i])*(l-num[i]);
		if(num[i]>r) res+=(num[i]-r)*(num[i]-r);
	}
	return res;
}
int main()
{
	freopen("skidesign.in","r",stdin);
	freopen("skidesign.out","w",stdout);
	int i;
	scanf("%d",&N);
	int minv=INF,maxv=-INF;
	for(i=1;i<=N;i++) 
	{
		scanf("%d",&num[i]);
		minv=min(minv,num[i]);
		maxv=max(maxv,num[i]);
	}
	int ans=INF;
	for(i=minv;i<=maxv-17;i++)
	{
		ans=min(ans,cal(i,i+17));
	}
	printf("%d\n",ans);
}
