/**************************************************************
    Problem: 1597
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:136 ms
    Memory:2268 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
const int MAXN=5e4+5;
 
int n,ncnt;
struct P{int x,y;} pt[MAXN];
inline bool cmp(const P &a,const P &b)
{return a.x<b.x||(a.x==b.x&&a.y<b.y);}
 
ll f[MAXN];
inline double K(int a,int b)
{return double(f[a]-f[b])/(pt[a+1].y-pt[b+1].y);}
 
int main()
{
    int i;scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d%d",&pt[i].x,&pt[i].y);
    std::sort(pt+1,pt+n+1,cmp);
    for(i=1;i<=n;i++) if(pt[i].y>pt[i+1].y)
    {
        while(ncnt&&pt[ncnt].y<=pt[i].y) ncnt--;
        pt[++ncnt]=pt[i];
    }
    static int dq[MAXN];int hd=1,tl=0;
    dq[++tl]=0;
    for(i=1;i<=n;i++)
    {
        while(hd<tl&&K(dq[hd],dq[hd+1])>=-pt[i].x)
            hd++;
        int j=dq[hd];
        f[i]=f[j]+(ll)pt[i].x*pt[j+1].y;
        while(hd<tl&&K(dq[tl],dq[tl-1])<K(dq[tl],i))
            tl--;
        dq[++tl]=i;
    }
    printf("%lld",f[ncnt]);
    return 0;
}
?
