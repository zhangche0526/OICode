/**************************************************************
    Problem: 2683
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:6300 ms
    Memory:35272 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
  
const int MAXN=5e5+5,MAXM=2e5+5;
  
int N;
  
int ans[MAXM],acnt;
  
struct Tri
{
    int x,y,ty,v,*ans;
    Tri(){};
    Tri(int x,int y,int ty,int *ans):x(x),y(y),ty(ty),v(0),ans(ans){}
    Tri(int x,int y,int v):x(x),y(y),ty(0),v(v),ans(NULL){}
} opt[MAXM<<2];int ocnt;
  
struct FT
{
    int na[MAXN];
    void add(int x,int v){for(;x<=N;x+=x&(-x)) na[x]+=v;}
    int sum(int x){if(!x) return 0;int res=0;for(;x;x-=x&(-x)) res+=na[x];return res;}
    void clean(int x){for(;x<=N;x+=x&(-x)) if(na[x]) na[x]=0;else return;}
} ft;
  
Tri tmp[MAXM<<2];
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
            if(!tmp[i].ty) ft.add(tmp[i].y,tmp[i].v);
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
    scanf("%d",&N);
    while(true)
    {
        int optTyp;scanf("%d",&optTyp);
        if(optTyp==1)
        {
            int x,y,v;scanf("%d%d%d",&x,&y,&v);
            ocnt++;opt[ocnt]=Tri(x,y,v);
        }else if(optTyp==2)
        {
            int x1,y1,x2,y2;scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            int *oa=&ans[++acnt];
            ocnt++;opt[ocnt]=Tri(x2,y2,1,oa);
            ocnt++;opt[ocnt]=Tri(x1-1,y2,-1,oa);
            ocnt++;opt[ocnt]=Tri(x2,y1-1,-1,oa);
            ocnt++;opt[ocnt]=Tri(x1-1,y1-1,1,oa);
        }else break;
    }
    cdq(1,ocnt);
    for(i=1;i<=acnt;i++) printf("%d\n",ans[i]);
    return 0;
}
