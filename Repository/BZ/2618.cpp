/**************************************************************
    Problem: 2618
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:4 ms
    Memory:1368 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
 
const int MAXN=505;
const double eps=1e-10;
 
struct P
{
    double x,y;
    P(double x=0,double y=0):x(x),y(y){};
};
P operator +(P a,P b){return P(a.x+b.x,a.y+b.y);}
P operator -(P a,P b){return P(a.x-b.x,a.y-b.y);}
double cross(P a,P b){return a.x*b.y-a.y*b.x;}
 
struct L
{
    P l,r;
    double ang;
    L(P l=P(),P r=P()):l(l),r(r)
    {ang=std::atan2(r.y-l.y,r.x-l.x);};
};
int cmpZero(double x){return x<-eps?-1:x>eps;}
 
bool cmp(L a,L b)
{
    int tmp=cmpZero(a.ang-b.ang);
    if(tmp) return tmp>0;
    return cmpZero(cross(a.l-b.r,b.l-b.r))<0;
}
P inter(L a,L b)
{
     double s1=cross(b.l-a.l,a.r-a.l),
            s2=cross(a.r-a.l,b.r-a.l);
     return P((b.l.x*s2+b.r.x*s1)/(s1+s2),
             (b.l.y*s2+b.r.y*s1)/(s1+s2));
}
bool jud(L l1,L l2,L l3)
{return cmpZero(cross(inter(l1,l2)-l3.r,l3.l-l3.r))<0;}
P pt[MAXN];int pcnt;
L ln[MAXN],deq[MAXN];int lcnt;
void calHPI()
{
    std::sort(ln+1,ln+lcnt+1,cmp);
    int i,tp=0,bt=1;
    int cnt=1;
    for(i=2;i<=lcnt;i++)
    {
        if(cmpZero(ln[i].ang-ln[i-1].ang)) cnt++;
        ln[cnt]=ln[i];
    }//选择性去除极角相同的半平面
    lcnt=cnt;
    deq[++tp]=ln[1];
    deq[++tp]=ln[2];
    for(i=3;i<=lcnt;i++)
    {
        while(bt<tp&&jud(deq[tp-1],deq[tp],ln[i]))
            tp--;
        while(bt<tp&&jud(deq[bt+1],deq[bt],ln[i]))
            bt++;
        deq[++tp]=ln[i];
    }
    while(bt<tp&&jud(deq[tp-1],deq[tp],deq[bt]))
        tp--;
    while(bt<tp&&jud(deq[bt+1],deq[bt],deq[tp]))
        bt++;
    for(i=bt;i<=tp-1;i++)
        pt[++pcnt]=inter(deq[i],deq[i+1]);
    pt[++pcnt]=inter(deq[tp],deq[bt]);
}
double calArea()
{
    double res=0;
    for(int i=2;i<pcnt;i++) 
        res+=cross(pt[1]-pt[i+1],pt[i]-pt[i+1]);
    return std::fabs(res)/2;
}
 
P dd[MAXN];
 
int main()
{
    int i,n,m;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&m);
        double x,y;
        for(i=1;i<=m;i++) scanf("%lf%lf",&x,&y),dd[i]=P(x,y);
        for(i=1;i<=m;i++) ln[++lcnt]=L(dd[i],dd[i==m?1:i+1]);
    }
    calHPI();
    printf("%.3f\n",calArea());
    return 0;
}
?
