#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>

const int MAXN=1e6+5;

int n;

struct P
{
	double x,y;
	P(double x=0,double y=0):x(x),y(y){};
} pt[MAXN],ch[MAXN];int ccnt;
P operator +(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}
double slope(P a,P b){return a.x==b.x?-1e60:(b.y-a.y)/(b.x-a.x);}
double slope(P a){return -std::sqrt(a.y/a.x);}
double calc(P a,double k){return k>=0?1e20:a.x+a.y-a.x*k-a.y/k;}
bool cmp(const P &a,const P &b){return a.x<b.x||(a.x==b.x&&a.y>b.y);}
inline void calCH()
{
	std::sort(pt+1,pt+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		while(ccnt>1&&cross(pt[i]-ch[ccnt],ch[ccnt]-ch[ccnt-1])<=0)
			ccnt--;
		ch[++ccnt]=pt[i];
	}
}

int main()
{
	int i;double ans=1e20;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%lf%lf",&pt[i].x,&pt[i].y);
	calCH();
	if(ccnt==1) ans=calc(ch[1],slope(ch[1]));
	else
	{
		double spL,spR,sp;
		spR=slope(ch[1],ch[2]),sp=slope(ch[1]);
		if(sp>=spR) ans=std::min(ans,calc(ch[1],sp));
		for(i=2;i<ccnt;i++)
		{
			spL=slope(ch[i-1],ch[i]),spR=slope(ch[i],ch[i+1]),sp=slope(ch[i]);
			ans=std::min(ans,calc(ch[i],spL));
			if(spL>=sp&&sp>=spR) ans=std::min(ans,calc(ch[i],sp));
		}
		spL=slope(ch[ccnt-1],ch[ccnt]),sp=slope(ch[ccnt]);
		ans=std::min(ans,calc(ch[ccnt],spL));
		if(sp<=spL) ans=std::min(ans,calc(ch[ccnt],sp));
	}
	printf("%.4lf\n",ans);
	return 0;
}
