/*
TASK:sort3
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#define min(a,b) (a<b?a:b)
using namespace std;

const int MAXN=1000;
int N;

int a[MAXN+1],b[MAXN+1];
int ch[9];
int ans;

void work(int & a,int & b)
{
	int minv=min(a,b);
	a-=minv,b-=minv;
	ans+=minv;
}

int main()
{
	freopen("sort3.in","r",stdin);
	freopen("sort3.out","w",stdout);
	int i;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i];
	}
	sort(b+1,b+N+1);
	for(i=1;i<=N;i++)
		if(a[i]!=b[i])
			++ch[(a[i]-1)*3+b[i]-1];
	work(ch[2],ch[6]);work(ch[1],ch[3]);work(ch[5],ch[7]);
	int tmp=0;
	for(i=0;i<=8;i++)
		tmp+=ch[i];
	ans+=tmp/3*2;
	printf("%d\n",ans);
	return 0;
}
