/**************************************************************
    Problem: 2002
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2192 ms
    Memory:6760 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
  
const int MAXN=2e5+5;
 
int n,m;
 
int k[MAXN];
 
struct N
{
    int val,c[2],fa,sz;bool rev;
} t[MAXN];
 
void upd(int x){t[x].sz=t[t[x].c[0]].sz+t[t[x].c[1]].sz+1;}
 
void pushdown(int x)
{
    if(t[x].rev)
    {
        t[t[x].c[0]].rev^=1;t[t[x].c[1]].rev^=1;
        t[x].rev^=1;std::swap(t[x].c[0],t[x].c[1]);
    }
}
  
inline bool isRt(int x){return t[t[x].fa].c[0]!=x&&t[t[x].fa].c[1]!=x;}
inline bool iden(int x){return t[t[x].fa].c[1]==x;}
void rot(int x)
{
    int y=t[x].fa,z=t[y].fa;
    pushdown(y);pushdown(x);
    bool xT=iden(x),yT=iden(y);
    if(!isRt(y)) t[z].c[yT]=x;
    t[x].fa=z;t[y].fa=x;t[t[x].c[!xT]].fa=y;
    t[y].c[xT]=t[x].c[!xT];t[x].c[!xT]=y;
    upd(y);upd(x);
}
void splay(int x)
{
    pushdown(x);
    while(!isRt(x))
    {
        int y=t[x].fa,z=t[y].fa;
        if(!isRt(y))
        {
            if(iden(x)^iden(y)) rot(x);
            else rot(y);
        } rot(x);
    }
}
  
void access(int x){for(int y=0;x;y=x,x=t[x].fa) splay(x),t[x].c[1]=y,upd(x);}
  
int findRt(int x){access(x);splay(x);while(t[x].c[0]) x=t[x].c[0];return x;}
  
void makeRt(int x){access(x);splay(x);t[x].rev^=1;}
  
void split(int x,int y){makeRt(x);access(y);splay(y);}
 
void cut(int x,int y){split(x,y);t[y].c[0]=t[x].fa=0;}
  
void link(int x,int y){makeRt(y);t[y].fa=x;}
  
int main()
{
    int i;
    scanf("%d",&n);
    for(i=1;i<=n+1;i++) t[i].sz=1;
    for(i=1;i<=n;i++)
    {
        scanf("%d",k+i);
        if(k[i]+i>n) k[i]=n+1-i;
        link(i+k[i],i);
    }
    scanf("%d",&m);
    while(m--)
    {
        int opt,x,v;
        scanf("%d%d",&opt,&x);x++;
        if(opt==1)
        {
            makeRt(n+1);
            makeRt(x);
            printf("%d\n",t[x].sz-1);
        }else
        {
            scanf("%d",&v);
            cut(x+k[x],x);
            k[x]=v;
            if(k[x]+x>n) k[x]=n+1-x;
            link(x+k[x],x);
        }
    }
    return 0;
}
