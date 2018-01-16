#include<iostream>
#include<cstdio>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
typedef long long ll;

const int MAXN=5e5+5,INF=1061109567;

int na[MAXN];

const int rt=1;
struct SEGTN
{
	int l,r,lc,rc;
	int mx1,mxc,mx2,mn1,mnc,mn2,det;ll sum;
} t[MAXN<<1];int tcnt=rt;
inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	t[o].sum=lc.sum+rc.sum;
	if(lc.mx1>rc.mx1) t[o].mx1=lc.mx1,t[o].mxc=lc.mxc,t[o].mx2=max(lc.mx2,rc.mx1);
	else if(lc.mx1<rc.mx1) t[o].mx1=rc.mx1,t[o].mxc=rc.mxc,t[o].mx2=max(lc.mx1,rc.mx2);
	else t[o].mx1=lc.mx1,t[o].mxc=lc.mxc+rc.mxc,t[o].mx2=max(lc.mx2,rc.mx2);
	if(lc.mn1<rc.mn1) t[o].mn1=lc.mn1,t[o].mnc=lc.mnc,t[o].mn2=min(lc.mn2,rc.mn1);
	else if(lc.mn1>rc.mn1) t[o].mn1=rc.mn1,t[o].mnc=rc.mnc,t[o].mn2=min(lc.mn1,rc.mn2);
	else t[o].mn1=lc.mn1,t[o].mnc=lc.mnc+rc.mnc,t[o].mn2=min(lc.mn2,rc.mn2);
}
inline void execDet(int o,int v)
{
	t[o].mx1+=v,t[o].mn1+=v;
	if(t[o].mx2!=-INF) t[o].mx2+=v;
	if(t[o].mn2!=INF) t[o].mn2+=v;
	t[o].sum+=(ll)v*(t[o].r-t[o].l+1);
}
inline void execMx(int o,int v)
{
	t[o].sum+=(ll)t[o].mnc*(v-t[o].mn1);
	t[o].mn1=v,umx(t[o].mx1,v);
	if(t[o].mx1==t[o].mn1)
	{
		t[o].mx2=-INF,t[o].mn2=INF;
		t[o].mxc=t[o].mnc=t[o].r-t[o].l+1;
		t[o].sum=(ll)v*(t[o].r-t[o].l+1);
	}else umx(t[o].mx2,v);
}
inline void execMn(int o,int v)
{
	t[o].sum-=(ll)t[o].mxc*(t[o].mx1-v);
	t[o].mx1=v,umn(t[o].mn1,v);
	if(t[o].mx1==t[o].mn1)
	{
		t[o].mx2=-INF,t[o].mn2=INF;
		t[o].mxc=t[o].mnc=t[o].r-t[o].l+1;
		t[o].sum=(ll)v*(t[o].r-t[o].l+1);
	}else umn(t[o].mn2,v);
}
inline void psd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(t[o].det)
	{
		execDet(t[o].lc,t[o].det);lc.det+=t[o].det;
		execDet(t[o].rc,t[o].det);rc.det+=t[o].det;
		t[o].det=0;
	}
	if(lc.mx1>t[o].mx1) execMn(t[o].lc,t[o].mx1);
	if(rc.mx1>t[o].mx1) execMn(t[o].rc,t[o].mx1);
	if(lc.mn1<t[o].mn1) execMx(t[o].lc,t[o].mn1);
	if(rc.mn1<t[o].mn1) execMx(t[o].rc,t[o].mn1);
}

void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r)
	{
		t[o].mx1=t[o].mn1=t[o].sum=na[l];
		t[o].mxc=t[o].mnc=1;
		t[o].mx2=-INF,t[o].mn2=INF;
		return;
	}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	upd(o);
}

void chDet(int o,int l,int r,int v)
{
	if(l<=t[o].l&&t[o].r<=r)
	{
		execDet(o,v);
		t[o].det+=v;
		return;
	}
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid) chDet(t[o].lc,l,r,v);
	if(r>mid) chDet(t[o].rc,l,r,v);
	upd(o);
}
void chMx(int o,int l,int r,int v)
{
	if(v<=t[o].mn1) return;
	if(l<=t[o].l&&t[o].r<=r)
		if(v<t[o].mn2) {execMx(o,v);return;}
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid) chMx(t[o].lc,l,r,v);
	if(r>mid) chMx(t[o].rc,l,r,v);
	upd(o);
}
void chMn(int o,int l,int r,int v)
{
	if(v>=t[o].mx1) return;
	if(l<=t[o].l&&t[o].r<=r)
		if(v>t[o].mx2) {execMn(o,v);return;}
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid) chMn(t[o].lc,l,r,v);
	if(r>mid) chMn(t[o].rc,l,r,v);
	upd(o);
}

int calMx(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].mx1;
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return max(calMx(t[o].lc,l,r),calMx(t[o].rc,l,r));
	if(l<=mid) return calMx(t[o].lc,l,r);
	return calMx(t[o].rc,l,r);
}
int calMn(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].mn1;
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return min(calMn(t[o].lc,l,r),calMn(t[o].rc,l,r));
	if(l<=mid) return calMn(t[o].lc,l,r);
	return calMn(t[o].rc,l,r);
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

int main()
{
	int i,n,m;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",na+i);
	buildTree(rt,1,n);
	scanf("%d",&m);
	while(m--)
	{
		int opt,l,r,v;scanf("%d%d%d",&opt,&l,&r);if(opt<=3) scanf("%d",&v);
		switch(opt)
		{
			case 1:chDet(rt,l,r,v);break;
			case 2:chMx(rt,l,r,v);break;
			case 3:chMn(rt,l,r,v);break;
			case 4:printf("%lld\n",calSum(rt,l,r));break;
			case 5:printf("%d\n",calMx(rt,l,r));break;
			case 6:printf("%d\n",calMn(rt,l,r));break;
		}
	}
	return 0;
}

/*
10
2 3 4 1 2 5 6 4 1 2
10
1 2 7 2
2 2 6 5
3 7 10 3
*/
