#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
inline void umn(int &a,int b){a=min(a,b);}
inline void umx(int &a,int b){a=max(a,b);}
using std::abs;
const int MAXN=5e5+5,INF=1061109567;

int n;

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
inline bool cmp(const P &a,const P &b)
{
	if(dms) return a.y<b.y||(a.y==b.y&&a.x<b.x);
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}

inline int dismn(int o,P p)
{
	if(!o) return INF;
	int res=0;
	if(p.x<t[o].mnp.x || p.x>t[o].mxp.x) res+= p.x<t[o].mxp.x ? t[o].mnp.x-p.x : p.x-t[o].mxp.x;
	if(p.y<t[o].mnp.y || p.y>t[o].mxp.y) res+= p.y<t[o].mxp.y ? t[o].mnp.y-p.y : p.y-t[o].mxp.y;
	return res;
}

inline int dismx(int o,P p)
{
	if(!o) return -INF;
	int res=0;
	res+=max(abs(t[o].mnp.x-p.x),abs(t[o].mxp.x-p.x));
	res+=max(abs(t[o].mnp.y-p.y),abs(t[o].mxp.y-p.y));
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
int ans;
void calMnDis(int o,P p)
{
	if(!o) return;
	if(pdis(p,t[o].p)) umn(ans,pdis(p,t[o].p));
	int c=dismn(t[o].lc,p)>dismn(t[o].rc,p);
	calMnDis(t[o].c[c],p);
	if(dismn(t[o].c[c^1],p)<ans)
		calMnDis(t[o].c[c^1],p);
}
void calMxDis(int o,P p)
{
	if(!o) return;
	if(pdis(p,t[o].p)) umx(ans,pdis(p,t[o].p));
	int c=dismx(t[o].lc,p)<dismx(t[o].rc,p);
	calMxDis(t[o].c[c],p);
	if(dismx(t[o].c[c^1],p)>ans)
		calMxDis(t[o].c[c^1],p);
}

inline void initKDT(){t[0].mnp=P(INF,INF),t[0].mxp=P(-INF,-INF);}
inline int calMnDis(P p){ans=INF;calMnDis(rt,p);return ans;}
inline int calMxDis(P p){ans=-INF;calMxDis(rt,p);return ans;}

int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d%d",&pt[i].x,&pt[i].y);
	initKDT();
	buildTree(rt,1,n,0);
	int ans=INF;
	for(i=1;i<=n;i++) umn(ans,calMxDis(pt[i])-calMnDis(pt[i]));
	printf("%d",ans);
	return 0;
}


/*
100
81 23
27 16
52 58
44 24
25 95
34 2
96 25
8 14
97 50
97 18
64 3
47 22
55 28
89 37
75 45
67 22
90 8
65 45
68 93
87 8
61 45
69 72
38 57
58 76
45 34
88 54
27 8
35 34
70 81
25 24
97 97
4 43
39 38
82 68
27 58
2 21
92 88
96 70
97 29
14 53
6 42
1 2
35 84
64 88
63 57
53 40
82 59
49 56
75 72
29 30
50 1
40 83
52 94
22 35
39 1
94 88
89 96
79 46
33 75
31 42
33 95
6 83
90 66
37 54
35 64
17 66
48 37
30 8
95 51
3 51
90 33
29 48
94 78
53 7
1 26
73 35
18 33
99 78
83 59
23 87
4 17
53 91
98 3
54 82
85 92
77 8
56 74
4 5
63 1
26 8
42 15
48 98
27 11
70 98
36 9
78 92
34 40
42 82
64 83
75 47
*/
