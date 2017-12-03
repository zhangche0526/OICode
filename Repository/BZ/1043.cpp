/**************************************************************
    Problem: 1043
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:292 ms
    Memory:1344 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
const int MAXN=1e3+5;
const double INF=1e60,PI=acos(-1);
 
int n;
 
struct P
{
    double x,y;
    P(double x=0,double y=0):x(x),y(y){};
};
P operator +(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double cross(P a,P b){return a.x*b.x+a.y*b.y;}
double dis(P a,P b){return std::sqrt(cross(b-a,b-a));}
 
struct C
{
    P cen;double r;
    C(P cen=P(),double r=0):cen(cen),r(r){};
} cir[MAXN];
struct R{double l,r;R(double l=0,double r=0):l(l),r(r){};} ran[MAXN];int rcnt;
bool cmp(const R &a,const R &b){return a.l<b.l;}
inline bool cntn(C a,C b){return a.r>=b.r+dis(a.cen,b.cen);}//a contains b
void inter(C a,C b)
{
    double d=dis(a.cen,b.cen),
           ang0=atan2(a.cen.x-b.cen.x,a.cen.y-b.cen.y),
           x=(a.r*a.r-b.r*b.r+d*d)/(2*d),
           angDet=acos(x/a.r);
    ran[++rcnt]=R(ang0-angDet,ang0+angDet);
}
double calc(int x)
{
    int i;
    for(i=x+1;i<=n;i++)
        if(cntn(cir[i],cir[x])) return 0;
    rcnt=0;
    for(i=x+1;i<=n;i++)
        if(!cntn(cir[x],cir[i])&&cir[x].r+cir[i].r>dis(cir[x].cen,cir[i].cen))
            inter(cir[x],cir[i]);
    double sum=0,now=0;
    for(i=1;i<=rcnt;i++)
    {
        if(ran[i].l<0) ran[i].l+=2*PI;
        if(ran[i].r<0) ran[i].r+=2*PI;
        if(ran[i].l>ran[i].r) ran[++rcnt]=R(0,ran[i].r),ran[i].r=2*PI;
    }
    std::sort(ran+1,ran+rcnt+1,cmp);
    for(i=1;i<=rcnt;i++)
        if(ran[i].l>now)
            sum+=ran[i].l-now,now=ran[i].r;
        else now=std::max(now,ran[i].r);
    sum+=2*PI-now;
    return sum*cir[x].r;
}
 
int main()
{
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        double x,y,r;scanf("%lf%lf%lf",&r,&x,&y);
        cir[i]=C(P(x,y),r);
    }
    double ans=0;
    for(i=1;i<=n;i++) ans+=calc(i);
    printf("%.3lf\n",ans);
}
