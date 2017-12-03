/**************************************************************
    Problem: 1588
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:176 ms
    Memory:1804 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#define x node[x_p]
#define y node[y_p]
#define z node[z_p]
#define p node[p_p]
#define u node[u_p]
#define v node[v_p]
#define min(a,b) (a<b?a:b)
using namespace std;
 
const int MAXN=32767,INF=~0U>>1;
 
struct splayTree
{
    int root,size;
    struct N
    {
        int lc,rc,fa;
        int val;
        N(){lc=rc=fa=val=0;}
    }node[MAXN+1];int ncnt;
    void lRotate(int x_p)
    {
        int y_p=x.rc;
        x.rc=y.lc;
        if(y.lc) node[y.lc].fa=x_p;
        y.fa=x.fa;
        if(!x.fa) root=y_p;
        else if(x_p==node[x.fa].lc) node[x.fa].lc=y_p;
        else node[x.fa].rc=y_p;
        y.lc=x_p,x.fa=y_p;
    }
    void rRotate(int x_p)
    {
        int y_p=x.lc;
        x.lc=y.rc;
        if(y.rc) node[y.rc].fa=x_p;
        y.fa=x.fa;
        if(!x.fa) root=y_p;
        else if(x_p==node[x.fa].lc) node[x.fa].lc=y_p;
        else node[x.fa].rc=y_p;
        y.rc=x_p,x.fa=y_p;
    }
    void splay(int x_p)
    {
        while(x.fa)
        {
            if(!node[x.fa].fa)
            {
                if(node[x.fa].lc==x_p) rRotate(x.fa);
                else lRotate(x.fa);
            }else if(node[x.fa].lc==x_p&&node[node[x.fa].fa].lc==x.fa)
            {
                rRotate(node[x.fa].fa);
                rRotate(x.fa);
            }else if(node[x.fa].rc==x_p&&node[node[x.fa].fa].rc==x.fa)
            {
                lRotate(node[x.fa].fa);
                lRotate(x.fa);
            }else if(node[x.fa].lc==x_p&&node[node[x.fa].fa].rc==x.fa)
            {
                rRotate(x.fa);
                lRotate(x.fa);
            }else
            {
                lRotate(x.fa);
                rRotate(x.fa);
            }
        }
    }
    int subtreeMin(int u_p)
    {
        while(node[u_p].lc) u_p=node[u_p].lc;
        return u_p;
    }
    int subtreeMax(int u_p)
    {
        while(node[u_p].rc) u_p=node[u_p].rc;
        return u_p;
    }
    splayTree(){root=0,size=0,ncnt=0;}
    void insert(int val)
    {
        int z_p=root;
        int p_p=0;
        while(z_p)
        {
            p_p=z_p;
            if(node[z_p].val<val) z_p=node[z_p].rc;
            else z_p=node[z_p].lc;
        }
        z_p=++ncnt;
        z.val=val;
        z.fa=p_p;
        if(!p_p) root=z_p;
        else if(p.val<z.val) p.rc=z_p;
        else p.lc=z_p;
        splay(z_p);
        ++size;
    }
    int work(int val)
    {
        insert(val);
        if(size==1) return val;
        if(!node[root].lc)
            return node[subtreeMin(node[root].rc)].val-val;
        if(!node[root].rc)
            return val-node[subtreeMax(node[root].lc)].val;
        return min(node[subtreeMin(node[root].rc)].val-val,
                val-node[subtreeMax(node[root].lc)].val);
    }
} spT;
 
int main()
{
    //freopen("xt.in","r",stdin);
    //freopen("xt.out","w",stdout);
    int i;
    int n;
    int ans=0;
    scanf("%d",&n);
    while(n--)
    {
        int rn;scanf("%d",&rn);
        ans+=spT.work(rn);
    }
    printf("%d\n",ans);
    return 0;
}
﻿
