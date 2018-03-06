/**************************************************************
    Problem: 2049
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1696 ms
    Memory:1488 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
 
const int MAXN=1e4+5;
int n,m;
struct N{int val,c[2],fa;bool rev;} t[MAXN];
 
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
 
void access(int x){for(int y=0;x;y=x,x=t[x].fa) splay(x),t[x].c[1]=y;}
 
int findRt(int x){access(x);splay(x);while(t[x].c[0]) x=t[x].c[0];return x;}
 
void makeRt(int x){access(x);splay(x);t[x].rev^=1;}
 
void split(int x,int y){makeRt(x);access(y);splay(y);}
 
void cut(int x,int y){split(x,y);t[y].c[0]=t[x].fa=0;}
 
void link(int x,int y){makeRt(y);t[y].fa=x;}
 
int main()
{
    int i;
    char opt[10];int x,y;
    scanf("%d%d",&n,&m);
    while(m--)
    {
        scanf("%s%d%d",opt,&x,&y);
        if(opt[0]=='C') link(x,y);
        else if(opt[0]=='D') cut(x,y);
        else
        {
            if(findRt(x)==findRt(y)) puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
