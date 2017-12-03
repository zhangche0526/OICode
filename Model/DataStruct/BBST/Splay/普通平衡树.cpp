#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=(int)1e5+5,INF=~0U>>1;

class SPT
{
    private:
        struct N
        {
            int val;
            int fa,c[2];
            int num,sz;//出现次数
        } t[MAXN];
        int sz,tcnt;//节点个数，已使用的数组元素个数
        int rt;
        
        void upd(int x)
        {t[x].sz=t[t[x].c[0]].sz+t[t[x].c[1]].sz+t[x].num;}

        bool iden(int x)//lc:0 rc:1
        {return t[t[x].fa].c[0]!=x;}
        
        void cnn(int x,int fa,bool son)
        {
            if(x) t[x].fa=fa;
            if(fa) t[fa].c[son]=x;
            else rt=x;
        }
        void rot(int x)
        {
            int y=t[x].fa,z=t[y].fa;
            bool xType=iden(x),yType=iden(y);
            cnn(t[x].c[!xType],y,xType);
            cnn(y,x,!xType);
            cnn(x,z,yType);
            upd(y);upd(x);
        }
        void splay(int x,int toFa)
        {
            while(t[x].fa!=toFa)
            {
                int xFa=t[x].fa;
                if(t[xFa].fa==toFa) rot(x);
                else
                {
                    if(iden(xFa)==iden(x)) {rot(xFa);rot(x);}
                    else {rot(x);rot(x);}
                }
            }
        }
        int find(int val)
        {
            int x=rt;
            while(x)
            {
                if(val==t[x].val) return x;
                if(val<t[x].val) x=t[x].c[0];
                else x=t[x].c[1];
            }
            return 0;
        }
        int stMin(int x)
        {
            int y=0;
            while(x){y=x;x=t[x].c[0];}
            return y;
        }
        int stMax(int x)
        {
            int y=0;
            while(x){y=x;x=t[x].c[1];}
            return y;
        }
    public:
        void insert(int val)
        {
            ++sz;
            int x=rt,y=0;
            while(x)
            {
                y=x;
                if(val==t[x].val)
                {
                    ++t[x].num;
                    splay(x,0);
                    return;
                }
                if(val<t[x].val) x=t[x].c[0];
                else x=t[x].c[1];
            }
            x=++tcnt;
            t[x].val=val,t[x].fa=y;
            t[x].num=t[x].sz=1; 
            cnn(x,y,val>t[y].val);
            splay(x,0);
        }
        void erase(int val)
        {
            --sz;
            int x=find(val);
            if(!x) return;
            if(t[x].num>1)
            {
                --t[x].num;
                splay(x,0);
                return;
            }
            splay(x,0);
            int y=stMax(t[x].c[0]),z=stMin(t[x].c[1]);
            if((!y)&&(!z)) rt=0,sz=0;
            else if(!y)
            {
                splay(z,0);
                t[z].c[0]=0;
                upd(z);
            }else if(!z)
            {
                splay(y,0);
                t[y].c[1]=0;
                upd(y);
            }else
            {
                splay(y,0);splay(z,y);
                t[z].c[0]=0;
                upd(z);upd(y);
            }
        }
        int lower(int val)
        {
            int x=rt,y=0;
            while(x)
            {
                if(t[x].val<val) y=x,x=t[x].c[1];
                else x=t[x].c[0];
            }
            return t[y].val;
        }
        int upper(int val)
        {
            int x=rt,y=0;
            while(x)
            {
                if(t[x].val>val) y=x,x=t[x].c[0];
                else x=t[x].c[1];
            }
            return t[y].val;
        }
        int n2r(int val)
        {
            insert(val);
            int res=t[t[rt].c[0]].sz+1;
            erase(val);
            return res;
        }
        int r2n(int k)
        {
            int x=rt;
            while(k<=t[t[x].c[0]].sz||k>t[t[x].c[0]].sz+t[x].num)
            {
                if(k<=t[t[x].c[0]].sz)
                    x=t[x].c[0];
                else k-=t[t[x].c[0]].sz+t[x].num,x=t[x].c[1];
            }
            return t[x].val;
        }
} spt;

int main()
{
    int n;scanf("%d",&n);
    while(n--)
    {
        int opt,x;scanf("%d%d",&opt,&x);
        if(opt==1) spt.insert(x);
        else if(opt==2) spt.erase(x);
        else if(opt==3) printf("%d\n",spt.n2r(x));
        else if(opt==4) printf("%d\n",spt.r2n(x));
        else if(opt==5) printf("%d\n",spt.lower(x));
        else if(opt==6) printf("%d\n",spt.upper(x));
    }
    return 0; 
}
