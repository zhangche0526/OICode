/**************************************************************
    Problem: 2716
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:60972 ms
    Memory:38400 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using std::min;
using std::max;
 
const int MAXN=5e5+5,MAXL=1e6+5;
 
int N,M;
 
struct Tri
{
    int id,x,y,*ans;
    Tri(){}
    Tri(int id,int x,int y,int *ans=NULL):id(id),x(x),y(y),ans(ans){}
} opt[MAXN<<1];int ocnt;
bool cmp(const Tri &a,const Tri &b){return a.id<b.id;}
 
int ans[MAXN],acnt;
 
int mxX,mxY;
 
struct FT
{
    int na[MAXL];
    void umx(int x,int v){for(;x<=mxY;x+=x&(-x)) na[x]=max(na[x],v);}
    int cmx(int x){int res=0;for(;x;x-=x&(-x)) res=max(res,na[x]);return res;}
    void clean(int x){for(;x<=mxY;x+=x&(-x)) if(na[x]) na[x]=0;else return;}
} ft;
 
Tri tmp[MAXN<<1];
void cdq(int l,int r)
{
    if(l==r) return;
    int i,mid=(l+r)>>1;
    cdq(l,mid);cdq(mid+1,r);
     
    int p1=l,p2=mid+1;
    for(i=l;i<=r;i++)
    {
        if(p2>r||(p1<=mid&&opt[p1].x<=opt[p2].x))
        {
            tmp[i]=opt[p1++];
            if(!tmp[i].ans) ft.umx(tmp[i].y,tmp[i].x+tmp[i].y);
        }
        else
        {
            tmp[i]=opt[p2++];
            if(tmp[i].ans)
            {
                int mx=ft.cmx(tmp[i].y);
                if(mx) *tmp[i].ans=min(*tmp[i].ans,tmp[i].x+tmp[i].y-mx);
            }
        }
    }
    for(i=l;i<=mid;i++) if(!opt[i].ans) ft.clean(opt[i].y);
    for(i=l;i<=r;i++) opt[i]=tmp[i];
}
 
int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++)
    {
        int x,y;scanf("%d%d",&x,&y);x++,y++;
        mxX=max(mxX,x),mxY=max(mxY,y);
        ocnt++;opt[ocnt]=Tri(ocnt,x,y);
    }
    for(i=1;i<=M;i++)
    {
        int optTyp;scanf("%d",&optTyp);
        int x,y;scanf("%d%d",&x,&y);x++,y++;
        mxX=max(mxX,x),mxY=max(mxY,y);
        if(optTyp==1) {ocnt++;opt[ocnt]=Tri(ocnt,x,y);}
        else {ocnt++;opt[ocnt]=Tri(ocnt,x,y,&ans[++acnt]);}
    }
    memset(ans,0x3f,sizeof ans);
    cdq(1,ocnt);
    for(i=1;i<=ocnt;i++) opt[i].x=mxX-opt[i].x+1;
    std::sort(opt+1,opt+ocnt+1,cmp);
    cdq(1,ocnt);
    for(i=1;i<=ocnt;i++) opt[i].y=mxY-opt[i].y+1;
    std::sort(opt+1,opt+ocnt+1,cmp);
    cdq(1,ocnt);
    for(i=1;i<=ocnt;i++) opt[i].x=mxX-opt[i].x+1;
    std::sort(opt+1,opt+ocnt+1,cmp);
    cdq(1,ocnt);
    for(i=1;i<=acnt;i++) printf("%d\n",ans[i]);
    return 0;
}
