#include<iostream>
#include<cstdio>
#include<algorithm>

struct P
{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){};
};

P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}

bool cmp(const P &a,const P &b)
{return a.x==b.x?(a.y<b.y):a.x<b.x;}

const int MAXN=2005;

int N;
P pt[MAXN],st[MAXN];int tp;

void push(P x,int btm)
{
	while(tp>btm&&cross(x-st[tp-1],st[tp]-st[tp-1])>=0)
		--tp;
	st[++tp]=x;
}

inline double RC()
{
	int i,j;
	double res=0;
	for(i=0;i<tp;i++)
	{
		int p1,p2;p1=p2=1;
		for(j=i+1;j<tp;j++)
		{
			while(cross(st[p1+1]-st[i],st[j]-st[i])>cross(st[p1]-st[i],st[j]-st[i]))
				p1=(p1+1)%tp;
			while(cross(st[j]-st[i],st[p2+1]-st[i])>cross(st[j]-st[i],st[p2]-st[i]))
				p2=(p2+1)%tp;
			res=std::max(res,cross(st[p1]-st[i],st[j]-st[i])+cross(st[j]-st[i],st[p2]-st[i]));
		}
	}
	return res/2;
}

int main()
{
	int i;
	scanf("%d",&N);
	for(i=1;i<=N;i++) scanf("%lf%lf",&pt[i].x,&pt[i].y);
	std::sort(pt+1,pt+N+1,cmp);
	st[++tp]=pt[1];
	for(i=2;i<=N;i++) push(pt[i],1);
	int tmp=tp;
	for(i=N-1;i>=1;i--) push(pt[i],tmp);
	tp--;st[0]=st[tp];
	printf("%.3f",RC());
	return 0;
}
