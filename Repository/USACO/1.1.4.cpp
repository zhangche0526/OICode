/*
ID:zhangch33
LANG:C++
TASK:beads
*/
#include<iostream>
#include<cstdio>
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
using namespace std;

const int MAXN=350;
int N;
int a[MAXN+1];

int cal(int sp)
{
	int i;
	int resr=1,resl=1,x=1,y=1;
	if(a[sp])
	{
		for(i=(sp>=N)?1:(sp+1);i!=sp;i=(i+1>N)?1:(i+1))
			if(a[i]!=(a[sp]==1?2:1)) ++resr;
			else break;
	}else
	{
		for(i=(sp>=N)?1:(sp+1);i!=sp;i=(i+1>N)?1:(i+1))
			if(a[i]!=1) ++x;
			else break;
		for(i=(sp>=N)?1:(sp+1);i!=sp;i=(i+1>N)?1:(i+1))
			if(a[i]!=2) ++y;
			else break;
		resr=max(x,y),x=y=0;
	}
	sp=sp==1?N:sp-1;
	if(a[sp])
	{
		for(i=(sp<=1)?N:sp-1;i!=sp;i=(i-1<1)?N:i-1)
			if(a[i]!=(a[sp]==1?2:1)) ++resl;
			else break;
	}else
	{
		for(i=(sp<=1)?N:sp-1;i!=sp;i=(i-1<1)?N:i-1)
			if(a[i]!=1) ++x;
			else break;
		for(i=(sp<=1)?N:sp-1;i!=sp;i=(i-1<1)?N:i-1)
			if(a[i]!=2) ++y;
			else break;
			resl=max(x,y);
	}int res=resl+resr;
	return res>N?N:res;
}

int main()
{
	freopen("beads.in","r",stdin);
	freopen("beads.out","w",stdout);
	int i;
	cin>>N;
	char x;
	for(i=1;i<=N;i++)
	{
		do x=getchar();
		while(x!='w'&&x!='b'&&x!='r');
		if(x=='b') a[i]=1;
		else if(x=='r') a[i]=2;
	}
	int maxv=0;
	for(i=1;i<=N;i++)
		maxv=max(maxv,cal(i));
	cout<<maxv<<endl;
	return 0;
}
