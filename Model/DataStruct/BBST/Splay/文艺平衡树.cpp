#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=100005;

int n,m;

void swap(int & a,int & b)
{int t=a;a=b;b=t;}

class SPT
{
    public:
    int root,size;
    private:
    struct N
    {
        int fa,c[2];
        int size;
        int val;
        bool tag;
    }t[MAXN];
    void update(int x)
    {t[x].size=t[t[x].c[0]].size+t[t[x].c[1]].size+1;}
    void cnn(int x,int fa,int cType)
    {
        if(x) t[x].fa=fa;
        if(fa) t[fa].c[cType]=x;
        else root=x;
    }
    bool iden(int x)
    {return t[t[x].fa].c[0]!=x;}
    void pushDown(int x)
    {
        if(t[x].tag)
        {
            swap(t[x].c[0],t[x].c[1]);
            t[t[x].c[0]].tag^=1,t[t[x].c[1]].tag^=1;
            t[x].tag=0;
        }
    }
    void rot(int x)
    {
        int y=t[x].fa,z=t[y].fa;
        bool xType=iden(x),yType=iden(y);
        cnn(t[x].c[!xType],y,xType);
        cnn(y,x,!xType);
        cnn(x,z,yType);
        update(y);update(x);
    }
    void splay(int x,int toFa)
    {
        while(t[x].fa!=toFa)
        {
            int xFa=t[x].fa;
            if(t[xFa].fa==toFa) rot(x);
            else if(iden(x)==iden(xFa))
                rot(xFa),rot(x);
            else rot(x),rot(x);
        }
    }
    int r2i(int rank)
    {
        int x=root;pushDown(x);
        while(rank!=t[t[x].c[0]].size+1)
        {
            if(rank<t[t[x].c[0]].size+1)
                x=t[x].c[0];
            else rank-=t[t[x].c[0]].size+1,x=t[x].c[1];
            pushDown(x);
        }
        return x;
    }
    public:
    int build(int l,int r)
    {
        if(l>r) return 0;
        int x=(l+r)>>1;
        cnn(build(l,x-1),x,0);
        cnn(build(x+1,r),x,1);
        ++size;
        t[x].val=x-1;
        update(x);
        return x;
    }
    void print(int x)
    {
        if(!x) return;
        pushDown(x);
        print(t[x].c[0]);
        if(x!=1&&x!=n+2) printf("%d ",t[x].val);
        print(t[x].c[1]);
    }
    void work(int l,int r)
    {
        int p1=r2i(l),p2=r2i(r+2);
        splay(p1,0),splay(p2,root);
        t[t[p2].c[0]].tag^=1;
    }
    int getRt(){return root;}
} spt;

int main()
{
    scanf("%d%d",&n,&m);
    spt.root=spt.build(1,n+2);
    while(m--)
    {
        int l,r;scanf("%d%d",&l,&r);
        spt.work(l,r);
    }
    spt.print(spt.getRt());
	return 0;
}
