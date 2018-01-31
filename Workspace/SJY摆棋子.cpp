#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
inline void umn(int &a,int b){a=min(a,b);}
inline void umx(int &a,int b){a=max(a,b);}
using std::abs;
const int MAXN=5e5+5,INF=1061109567;

int n,m;

struct P
{
	int x,y;
	P(int x=0,int y=0):x(x),y(y){}
} pt[MAXN];
inline int pdis(P a,P b){return abs(a.x-b.x)+abs(a.y-b.y);}

#define lc c[0]
#define rc c[1]
int rt;
struct KDTN
{
	int c[2];
	P p,mnp,mxp;
	KDTN(){}
	KDTN(P p):p(p),mnp(p),mxp(p){lc=rc=0;}
} t[MAXN<<1];int tcnt;

bool dms;
bool cmp(const P &a,const P &b)
{
	if(dms) return a.y<b.y||(a.y==b.y&&a.x<b.x);
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

inline int rdis(int o,P p)
{
	if(!o) return INF;
	int res=0;
	if(p.x<t[o].mnp.x || p.x>t[o].mxp.x) res+= p.x<t[o].mxp.x ? t[o].mnp.x-p.x : p.x-t[o].mxp.x;
	if(p.y<t[o].mnp.y || p.y>t[o].mxp.y) res+= p.y<t[o].mxp.y ? t[o].mnp.y-p.y : p.y-t[o].mxp.y;
	return res;
}

inline void upd(int o)
{
	KDTN &l=t[t[o].lc],&r=t[t[o].rc];
	umn(t[o].mnp.x,min(l.mnp.x,r.mnp.x));
	umn(t[o].mnp.y,min(l.mnp.y,r.mnp.y));
	umx(t[o].mxp.x,max(l.mxp.x,r.mxp.x));
	umx(t[o].mxp.y,max(l.mxp.y,r.mxp.y));
}

void buildTree(int &o,int l,int r,int d)
{
	if(l>r) return;
	if(!o) o=++tcnt;
	dms=d;
	int mid=(l+r)>>1;
	std::nth_element(pt+l,pt+mid,pt+r+1,cmp);
	t[o]=KDTN(pt[mid]);
	buildTree(t[o].lc,l,mid-1,d^1);
	buildTree(t[o].rc,mid+1,r,d^1);
	upd(o);
}

int calMnDis(int o,P p)
{
	if(!o) return INF;
	int res=pdis(p,t[o].p);
	int c=rdis(t[o].lc,p)>rdis(t[o].rc,p);
	umn(res,calMnDis(t[o].c[c],p));
	if(rdis(t[o].c[c^1],p)<res)
		umn(res,calMnDis(t[o].c[c^1],p));
	return res;
}

void addPt(int &o,P p)
{
	if(!o) {t[o=++tcnt]=KDTN(p);return;}
	int d=cmp(p,t[o].p)^1;dms^=1;
	addPt(t[o].c[d],p);
	upd(o);
}

inline void initKDT(){t[0].mnp=P(INF,INF),t[0].mxp=P(-INF,-INF);}
inline void mdf(P p){dms=0;addPt(rt,p);}
inline int qry(P p){return calMnDis(rt,p);}

int main()
{
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d%d",&pt[i].x,&pt[i].y);
	initKDT();
	buildTree(rt,1,n,0);
	for(i=1;i<=m;i++)
	{
		int opt;P p;scanf("%d%d%d",&opt,&p.x,&p.y);
		if(opt==1) mdf(p);
		else printf("%d\n",qry(p));
	}
	return 0;
}

