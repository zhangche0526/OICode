/**************************************************************
    Problem: 1878
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2656 ms
    Memory:35860 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
 
const int MAXN=5e4+5;
 
struct TN{int lc,rc,sz;} t[MAXN*25];int tcnt;
int rt[MAXN];
void insert(int l,int r,int x,int &y,int k)
{
    y=++tcnt;
    t[y]=t[x];
    t[y].sz++;
    if(l==r) return;
    int mid=l+r>>1;
    if(k<=mid) insert(l,mid,t[x].lc,t[y].lc,k);
    else insert(mid+1,r,t[x].rc,t[y].rc,k);
}
int calc(int l,int r,int x,int y,int v)
{
    if(r<v) return 0;
    if(l>=v) return t[y].sz-t[x].sz;
    int mid=l+r>>1;
    return calc(l,mid,t[x].lc,t[y].lc,v)+calc(mid+1,r,t[x].rc,t[y].rc,v);
}
int n,m;
 
int la[MAXN*100],nextPos[MAXN];
int main()
{
    int i,x;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&x);
        if(la[x]) nextPos[la[x]]=i;
        la[x]=i;
    }
    for(i=1;i<=n;i++) if(!nextPos[i]) nextPos[i]=n+1;
    for(i=1;i<=n;i++) insert(1,n+1,rt[i-1],rt[i],nextPos[i]);
    scanf("%d",&m);
    for(i=1;i<=m;i++)
    {
        int l,r;scanf("%d%d",&l,&r);    
        printf("%d\n",calc(1,n+1,rt[l-1],rt[r],r+1));
    }
}
