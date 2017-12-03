#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

const double eps=1e-8;
const int MAXN=5e4+5;

int n;

struct L {double k,b;int id;} ln[MAXN];
bool cmp(const L &a,const L &b)
{return a.k<b.k||(fabs(a.k-b.k)<eps&&a.b<b.b);}

double crossx(L a,L b)
{return (b.b-a.b)/(a.k-b.k);}

L st[MAXN];int tp;
bool chs[MAXN];

void insert(L rLn)
{
	while(tp)
	{
		if(fabs(st[tp].k-rLn.k)<eps) tp--;
		else if(tp>1&&crossx(rLn,st[tp-1])<=crossx(st[tp],st[tp-1])) tp--;
		else break;
	}
	st[++tp]=rLn;
}

int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	    scanf("%lf%lf",&ln[i].k,&ln[i].b),ln[i].id=i;
    std::sort(ln+1,ln+n+1,cmp);
   	for(i=1;i<=n;i++) insert(ln[i]);
    for(i=1;i<=tp;i++) chs[st[i].id]=true;
    for(i=1;i<=n;i++) if(chs[i]) printf("%d ",i);
    printf("\n");
	return 0;
}
