#include<iostream>
#include<cstdio>
using std::min;
using std::max;
int read()
{
	int res=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') res=res*10+c-'0',c=getchar();
	return res;
}

const int MAXN=1e6+5;

const int rt=1;int na[MAXN];
struct SEGTN{int l,r,lc,rc;int mx,cnt,nd;ll sum;int tag;} t[MAXN<<1];int tcnt;
inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	t[o].sum=lc.sum+rc.sum;
	if(lc.mx<rc.mx) t[o].mx=lc.mx,t[o].cnt=lc.cnt,t[o].nd=rc.mx;
	else if(lc.mx>rc.mx) t[o].mx=rc.mx,t[o].cnt=rc.cnt,t[o].nd=lc.mx;
	else t[o].mx=lc.mx,t[o].cnt=lc.cnt+rc.cnt,t[o].nd=max(lc.nd,rc.nd);
}
inline void psd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	lc.tag=rc.tag=t[o].tag;
	t[o].tag=0;
}
void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) {t[o].mx=na[l],t[o].cnt=1,sum=nd=0;return;}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	upd(o);
}

void ch(int o,int l,int r,int v)
{
	if(l<=t[o].l&&t[o].r<=r)
	{

	}
}
ll calSum(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return calSum(t[o].lc,l,r)+calSum(t[o].rc,l,r);
	if(l<=mid) return calSum(t[o].lc,l,r);
	return calSum(t[o].rc,l,r);
}
int calMx(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].mx;
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return max(calMx(t[o].lc,l,r),calMx(t[o].rc,l,r));
	if(l<=mid) return calSum(t[o].lc,l,r);
	return calSum(t[o].rc,l,r);
}

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int i;
		int opt,x,y,t;scanf("%d%d%d",&opt,&x,&y);
		switch(opt)
		{
			case 0:scanf("%d",&t);mdf(x,y,t);break;
			case 1:printf("%d\n",qry1(x,y));break;
			case 2:printf("%d\n",qry2(x,y));break;
		}
	}
	return 0;
}
