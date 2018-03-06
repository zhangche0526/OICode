#include<iostream>
#include<cstdio>

const int MAXN=1e7+5,MAXM=1005;

const int rt=1;
struct SEGTN
{
	int l,r,lc,rc;
	bool occ,tag;
} t[MAXN<<1];int tcnt=rt;

void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) return;
	int mid=l+r>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
}

inline void pushdown(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(t[o].tag)
	{
		lc.occ=rc.occ=true;
		t[o].tag=false;
	}
}

inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(lc.occ&&rc.occ) t[o].occ=true;
}

bool qry(int o,int l,int r)
{
	if(t[o].occ) return false;
	if(l<=t[o].l&&t[o].r<=r)
	{
		t[o].occ=t[o].tag=true;
		return true;
	}
	int mid=t[o].l+t[o].r>>1;
	pushdown(o);
	bool res=false;
	if(l<=mid) res|=qry(t[o].lc,l,r);
	if(r>mid) res|=qry(t[o].rc,l,r);
	upd(o);
	return res;
}
inline bool qry(int l,int r){return qry(rt,l,r);}

int n,m;

int main()
{
	int i;scanf("%d%d",&n,&m);
	buildTree(rt,1,n);
	static int L[MAXM],R[MAXM];
	for(i=1;i<=m;i++) scanf("%d%d",L+i,R+i);
	int ans=0;
	for(i=m;i;i--) ans+=qry(L[i],R[i]);
	printf("%d",ans);
	return 0;
}

