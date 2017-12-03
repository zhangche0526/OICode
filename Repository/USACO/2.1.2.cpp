/*
TASK:frac1
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=160;
int N;

int gcd(int a,int b){return b==0?a:gcd(b,a%b);}

struct F
{
	int a,b;
	bool operator != (const F & ot)
	{
		if(ot.a!=a||ot.b!=b) return true;
		return false;
	}
	void reduce()
	{
		int gcdnum=gcd(a,b);
		a/=gcdnum,b/=gcdnum;
	}
} frac[MAXN*MAXN];int fcnt;
bool cmp(const F & a,const F & b)
{
	if(a.b==b.b) return a.a<b.a;
	return a.a*b.b<b.a*a.b;
}

int main()
{
	freopen("frac1.in","r",stdin);
	freopen("frac1.out","w",stdout);
	int i,j;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
		for(j=0;j<=i;j++)
		{
			frac[++fcnt]=(F){j,i};
			frac[fcnt].reduce();
		}
	sort(frac+1,frac+fcnt+1,cmp);
	for(i=1;i<fcnt;i++)
		if(frac[i]!=frac[i+1])
			printf("%d/%d\n",frac[i].a,frac[i].b);
	printf("%d/%d\n",frac[fcnt].a,frac[fcnt].b);
}
