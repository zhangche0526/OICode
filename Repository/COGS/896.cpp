#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

const int MAXN=1e4+5;
int n;

struct P
{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){};
} pt[MAXN];
P operator +(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}
double dot(P a,P b){return a.x*b.x+a.y*b.y;}
double dis(P a,P b){return sqrt(dot(b-a,b-a));}

P ch[MAXN];int ccnt;
bool cmp(const P &a,const P &b)
{return a.x<b.x||(a.x==b.x&&a.y<b.y);}

void calCH()
{
	int i;
	std::sort(pt+1,pt+n+1,cmp);
	for(i=1;i<=n;i++)
	{
		while(ccnt>1&&cross(ch[ccnt]-ch[ccnt-1],pt[i]-ch[ccnt-1])<=0)
			ccnt--;
		ch[++ccnt]=pt[i];
	}
	int tmp=ccnt;
	for(i=n-1;i;i--) 
	{
		while(ccnt>tmp&&cross(ch[ccnt]-ch[ccnt-1],pt[i]-ch[ccnt-1])<=0)
			ccnt--;
		ch[++ccnt]=pt[i];
	}
	if(n>1) ccnt--;
}

int main()
{
	freopen("fc.in","r",stdin);
	freopen("fc.out","w",stdout);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		double x,y;scanf("%lf%lf",&x,&y);
		pt[i]=P(x,y);
	}
	calCH();
	double ans=0;
	for(i=1;i<=ccnt;i++) ans+=dis(ch[i],ch[i+1]);
	printf("%.2lf\n",ans);
	return 0;
}
