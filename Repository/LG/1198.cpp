#include<iostream>
#include<cstdio>
#define max(a,b) (a>b?a:b)
using namespace std;

typedef long long ll;
const int MAXM=(int)2e5+10;
const ll INF=~0ULL>>1;

int M;
int at,D;

struct N{int lc,rc,l,r;int max;} t[2*MAXM];int tcnt;

int na[MAXM];int ncnt;

void update(int o)
{t[o].max=max(t[t[o].lc].max,t[t[o].rc].max);}

void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r)
	{
		t[o].max=na[l];
		return;
	}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	update(o);
}

int calMax(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r)
		return t[o].max;
	int mid=(t[o].l+t[o].r)>>1;
	ll lmax=-INF,rmax=-INF;
	if(l<=mid) lmax=calMax(t[o].lc,l,r);
	if(r>mid) rmax=calMax(t[o].rc,l,r);
	return max(lmax,rmax);
}

void chDet(int o,int p,int x)
{
	if(t[o].l==t[o].r&&t[o].l==p)
	{
		t[o].max+=x;
		return;
	}
	int mid=(t[o].l+t[o].r)>>1;
	if(p<=mid) chDet(t[o].lc,p,x);
	else chDet(t[o].rc,p,x);
	update(o);
}

int main()
{
	scanf("%d%I64d",&M,&D);
	int root=1;
	buildTree(root,1,M);
	while(M--)
	{
		char c[2];scanf("%s",&c);
		int x;scanf("%d",&x);
		if(c[0]=='A')
			chDet(root,++ncnt,(x+at)%D);
		else
		{
			at=calMax(root,ncnt-x+1,ncnt);
			printf("%I64d\n",at);
		}
	}
	return 0;
}


