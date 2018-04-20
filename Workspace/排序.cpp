#include<iostream>
#include<cstdio>

const int MAXN=1e5+5;

int n,m,q;
int na[MAXN],ans;

struct O{int t,l,r;} opt[MAXN];

const int rt=1;
struct SEGTN{int l,r,lc,rc,cnt,tag;} t[MAXN<<1];int tcnt;
inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	t[o].cnt=lc.cnt+rc.cnt;
}
void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;t[o].tag=-1;
	if(l==r){t[o].cnt=na[l]>=ans;return;}
	int mid=l+r>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	upd(o);
}
inline void psd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(~t[o].tag)
	{
		lc.cnt=t[o].tag*(lc.r-lc.l+1),rc.cnt=t[o].tag*(rc.r-rc.l+1);
		lc.tag=rc.tag=t[o].tag;
		t[o].tag=-1;
	}
}
void chClr(int o,int l,int r,int v)
{
	if(l<=t[o].l&&t[o].r<=r) {t[o].cnt=v*(t[o].r-t[o].l+1),t[o].tag=v;return;}
	int mid=t[o].l+t[o].r>>1;
	psd(o);
	if(l<=mid) chClr(t[o].lc,l,r,v);
	if(r>mid) chClr(t[o].rc,l,r,v);
	upd(o);
}
int calCnt(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].cnt;
	int mid=t[o].l+t[o].r>>1;
	psd(o);
	if(l<=mid&&r>mid) return calCnt(t[o].lc,l,r)+calCnt(t[o].rc,l,r);
	if(l<=mid) return calCnt(t[o].lc,l,r);
	return calCnt(t[o].rc,l,r);
}

inline void mdf(O opt)
{
	int cnt[2];cnt[1]=calCnt(rt,opt.l,opt.r);
	cnt[0]=opt.r-opt.l+1-cnt[1];
	if(cnt[opt.t]) chClr(rt,opt.l,opt.l+cnt[opt.t]-1,opt.t);
	if(cnt[opt.t^1]) chClr(rt,opt.l+cnt[opt.t],opt.r,opt.t^1);
}

inline bool check(int mid)
{
	ans=mid;
	tcnt=rt;buildTree(rt,1,n);
	for(int i=1;i<=m;i++)
		mdf(opt[i]);
	return calCnt(rt,q,q);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("sort10.in","r",stdin);
#endif
	int i;scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",na+i);
	for(i=1;i<=m;i++)
	{
		int t,l,r;scanf("%d%d%d",&t,&l,&r);
		opt[i]=(O){t,l,r};
	}
	scanf("%d",&q);
	int l=1,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d",r);
	return 0;
}
/*
6 3
1 6 2 5 3 4
0 1 4
1 3 6
0 2 4
3
*/
