#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=5e5;
int n,m;
int D[MAXN+1];

int preSum[MAXN+1];
int calSum(int l,int r){return preSum[r]-preSum[l-1];}

int maxPre[MAXN+1],maxSuf[MAXN+1],maxSub[MAXN+1][2];

struct T{int a,b,lc,rc;} tree[MAXN+1];int tcnt;

int buildTree(int l,int r)
{
	++tcnt;
	int o=tcnt;
	tree[o].a=l,tree[o].b=r;
	if(l==r)
	{
		maxPre[o]=maxSuf[o]=l;
		maxSub[o][0]=maxSub[o][1]=l;
		return o;
	}
	int mid=(l+r)>>1;
	tree[o].lc=buildTree(l,mid);
	tree[o].rc=buildTree(mid+1,r);

	int lv,rv;

	lv=calSum(l,maxPre[lc]),rv=calSum(l,maxPre[rc]);
	maxPre[o]=lv>rv?maxPre[lc]:maxPre[rc];

	lv=calSum(maxSuf[lc],r),rv=calSum(maxSuf[rc],r);
	maxSuf[o]=lv>rv?maxSuf[lc]:maxSuf[rc];

	lv=sum(maxSub[lc][0],maxSub[lc][1]),rv=(maxSub[rc],maxSub[rc][1]);
	int lrv=max(lv,rv);
	int midv=sum(maxPre[o],maxSuf[o]);
	if(lrv>midv)
	{
		if(lv>rv) maxSub[o][0]=maxSub[lc][0],maxSub[o][1]=maxSub[lc][1];
		else maxSub[o][0]=maxSub[rc][0],maxSub[o][1]=maxSub[rc][1];
	}else maxSub[o][0]=maxPre[o],maxSub[o][1]=maxSuf[o];
}

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		int i;
		scanf("%d",&m);
		for(i=1;i<=n;i++) scanf("%d",&D[i]);
		
	}
	return 0;
}
