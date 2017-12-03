#include<iostream>
#include<cstdio>
#define rt 1

const int MAXN=2e5+5,INF=~0U>>1;

int M,D;
int ncnt,T;

struct SEGTN{int l,r,lc,rc;int mx;} t[MAXN<<2];int tcnt=rt;
void update(int o){t[o].mx=std::max(t[t[o].lc].mx,t[t[o].rc].mx);}
void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
}
void change(int o,int p,int v)
{
	if(t[o].l==t[o].r&&t[o].l==p){t[o].mx=v;return;}
	int mid=(t[o].l+t[o].r)>>1;
	if(p<=mid) change(t[o].lc,p,v);
	else change(t[o].rc,p,v);
	update(o);
}
int calMX(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].mx;
	int mid=(t[o].l+t[o].r)>>1;
	int lmx=-INF,rmx=-INF;
	if(l<=mid) lmx=calMX(t[o].lc,l,r);
	if(r>mid) rmx=calMX(t[o].rc,l,r);
	return std::max(lmx,rmx);
}

int main()
{
	int i;
	scanf("%d%d",&M,&D);
	buildTree(rt,1,M);
	for(i=1;i<=M;i++)
	{
		char opt[10];
		scanf("%s",opt);
		if(opt[0]=='Q')
		{
			int L;scanf("%d",&L);
			T=calMX(1,ncnt-L+1,ncnt);
			printf("%d\n",T);
		}else
		{
			int n;scanf("%d",&n);
			change(1,++ncnt,(n+T)%D);
		}
	}
	return 0;
}
