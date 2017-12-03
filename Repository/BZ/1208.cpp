/**************************************************************
    Problem: 1208
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:188 ms
    Memory:2548 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#define x node[x_p]
#define y node[y_p]
#define z node[z_p]
#define u node[u_p]
#define v node[v_p]
#define p node[p_p]
using namespace std;
  
const int MAXN=80000,INF=~0U>>1,P=1000000;
  
struct splayTree
{
    int root,size;
    int type;
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
    void replace(int u_p,int v_p)
    {
        if(!u.fa) root=v_p;
        else if(u_p==node[u.fa].lc) node[u.fa].lc=v_p;
        else node[u.fa].rc=v_p;
        if(v_p) v.fa=u.fa;
    }
    int subtreeMin(int u_p)
    {
        while(node[u_p].lc) u_p=node[u_p].lc;
        return u_p;
    }
    splayTree(){root=size=ncnt=type=0;}
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
    void erase(int z_p)
    {
        splay(z_p);
        if(!z.lc) replace(z_p,z.rc);
        else if(!z.rc) replace(z_p,z.lc);
        else
        {
            int y_p=subtreeMin(z.rc);
            if(y.fa!=z_p)
            {
                replace(y_p,y.rc);
                y.rc=z.rc;
                node[y.rc].fa=y_p;
            }
            replace(z_p,y_p);   
            y.lc=z.lc;
            node[y.lc].fa=y_p;
        }
        --size;
    }
    int work(int val,int rtype)
    {
        if(!size) {type=rtype;insert(val);return 0;}
        if(rtype==type) {insert(val);return 0;}
        int x_p=-1,y_p=-1,u_p=root;
        while(u_p)
            if(u.val<=val)
            {
                x_p=u_p;
                u_p=u.rc;
            }else u_p=u.lc;
        u_p=root;
        while(u_p)
            if(u.val>=val)
            {
                y_p=u_p;
                u_p=u.lc;
            }else u_p=u.rc;
        if(x_p==-1) x_p=y_p;
        else if(y_p!=-1)
            if(y.val-val<val-x.val) x_p=y_p;
        erase(x_p);
        return x.val>val?x.val-val:val-x.val;
    }
} spT;
 
int main()
{ 
    int i;int n;int ans=0;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        int rtype,val;
        scanf("%d%d",&rtype,&val);
        ans=(ans+spT.work(val,rtype))%P;
    }
    printf("%d\n",ans);
    return 0;
}
