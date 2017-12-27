#include<iostream>
#include<cstdio>
using std::min;
using std::max;

const int MAXN=5e4+5;

int n,m;

const int rt=1;
struct SEGTN{int l,r,lc,rc;int mxv;bool blk;} t[MAXN<<2];int tcnt=rt;
void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) {t[o].blk=true;return;}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
}

inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	t[o].mxv=max(lc.mxv,rc.mxv);
	t[o].blk=lc.blk|rc.blk;
}
void pCh(int o,int p,int v)
{
	if(t[o].l==t[o].r) {t[o].mxv=v,t[o].blk=false;return;}
	int mid=(t[o].l+t[o].r)>>1;
	if(p<=mid) pCh(t[o].lc,p,v);
	else pCh(t[o].rc,p,v);
	upd(o);
}

bool calBlk(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].blk;
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return calBlk(t[o].lc,l,r)|calBlk(t[o].rc,l,r);
	if(l<=mid) return calBlk(t[o].lc,l,r);
	return calBlk(t[o].rc,l,r);
}
int calMx(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].mxv;
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return max(calMx(t[o].lc,l,r),calMx(t[o].rc,l,r));
	if(l<=mid) return calMx(t[o].lc,l,r);
	return calMx(t[o].rc,l,r);
}

int na[MAXN];
int main()
{
	int i;
	scanf("%d",&n);buildTree(rt,1,5e4);
	for(i=1;i<=n;i++)
	{
		int p,v;scanf("%d%d",&p,&v);
		na[p]=v;pCh(rt,p,v);
	}
	scanf("%d",&m);
	for(i=1;i<=m;i++)
	{
		int l,r;scanf("%d%d",&l,&r);l++;
		if(calMx(rt,l,r)!=na[r]) puts("false");
		else if(calBlk(rt,l,r)) puts("maybe");
		else puts("true");
	}
	return 0;
}
