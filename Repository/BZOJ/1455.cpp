/**************************************************************
    Problem: 1455
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2204 ms
    Memory:20824 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
 
const int MAXN=1e6+5;
 
int n,m;
 
struct LT{int lc,rc,d,w;} t[MAXN];
 
int fa[MAXN];
int findAnc(int x){return fa[x]==x?x:findAnc(fa[x]);}
int merge(int x,int y)
{
    if(!x) return y;
    if(!y) return x;
    if(t[x].w>t[y].w) std::swap(x,y);
    t[x].rc=merge(t[x].rc,y);
    if(t[t[x].lc].d<t[t[x].rc].d) std::swap(t[x].lc,t[x].rc);
    t[x].d=t[t[x].rc].d+1;
    return x;
}
void pop(int x)
{
    t[x].w=-1;
    int r=merge(t[x].lc,t[x].rc);
    fa[x]=fa[r]=r;
}
 
int main()
{
    int i;
    scanf("%d",&n);
    //t[0].d=-1;
    for(i=1;i<=n;i++) scanf("%d",&t[i].w),fa[i]=i;
    scanf("%d",&m);
    while(m--)
    {
        char opt[10];scanf("%s",opt);
        if(opt[0]=='M')
        {
            int x,y;scanf("%d%d",&x,&y);
            if(!(~t[x].w)||!(~t[y].w)) continue;
            x=findAnc(x),y=findAnc(y);
            if(x!=y) fa[x]=fa[y]=merge(x,y);
        }
        else
        {
            int x;scanf("%d",&x);
            if(~t[x].w)
            {
                x=findAnc(x);
                printf("%d\n",t[x].w);
                pop(x);
            }else puts("0");
        }
    }
    return 0;
}
