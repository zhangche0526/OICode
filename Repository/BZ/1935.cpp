/**************************************************************
    Problem: 1935
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:5180 ms
    Memory:139964 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
 
const int MAXN=5e5+5,MAXL=1e7+5;
 
int N,M;
 
int ans[MAXN],acnt;
 
struct Tri
{
    int id,x,y,ty,*ans;
    Tri(){};
    Tri(int x,int y,int ty,int *ans):x(x),y(y),ty(ty),ans(ans){}
    Tri(int x,int y):x(x),y(y),ty(0),ans(NULL){}
} opt[MAXN*5];int ocnt;
 
struct FT
{
    int na[MAXL];
    void add(int x){for(;x<=N;x+=x&(-x)) na[x]++;}
    int sum(int x){if(!x) return 0;int res=0;for(;x;x-=x&(-x)) res+=na[x];return res;}
    void clean(int x){for(;x<=N;x+=x&(-x)) if(na[x]) na[x]=0;else return;}
} ft;
 
Tri tmp[MAXN*5];
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
            if(!tmp[i].ty) ft.add(tmp[i].y);
        }else
        {
            tmp[i]=opt[p2++];
            if(tmp[i].ty) *tmp[i].ans+=ft.sum(tmp[i].y)*tmp[i].ty;
        }
    }
    for(i=l;i<=mid;i++) if(!opt[i].ty) ft.clean(opt[i].y);
    for(i=l;i<=r;i++) opt[i]=tmp[i];
}
 
int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<=N;i++)
    {
        int x,y;scanf("%d%d",&x,&y);x++,y++;
        ocnt++;opt[ocnt]=Tri(x,y);
    }
    for(i=1;i<=M;i++)
    {
        int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);x1++,y1++,x2++,y2++;
        int *oa=&ans[++acnt];
        ocnt++;opt[ocnt]=Tri(x2,y2,1,oa);
        ocnt++;opt[ocnt]=Tri(x1-1,y2,-1,oa);
        ocnt++;opt[ocnt]=Tri(x2,y1-1,-1,oa);
        ocnt++;opt[ocnt]=Tri(x1-1,y1-1,1,oa);
    }
    cdq(1,ocnt);
    for(i=1;i<=acnt;i++) printf("%d\n",ans[i]);
    return 0;
}
