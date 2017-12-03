#include <cstdio>
#include <cstdlib>
using namespace std;

const int MAXN=100005;


class TREAP
{
	private:
        struct N
        {
            int val;
            int fa,c[2];
            int num,sz;//出现次数
            int w;
        } t[MAXN];
		int sz,tcnt;int rt;

		void upd(int x)
		{t[x].sz=t[t[x].c[0]].sz+t[t[x].c[1]].sz+t[x].num;}
		void pushup(int x)
		{while(x){upd(x);x=t[x].fa;}}

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
		int find(int val)
		{
			int x=rt;
			while(x)
			{
				if(t[x].val==val) return x;
				x=t[x].c[val>t[x].val];
			}
			return 0;
		}
		int stLim(int x,bool type)
		{
			int y=0;
			while(x)
			{
				y=x;
				x=t[x].c[type];
			}
			return y;
		}
	public:
		void insert(int val)
		{
			++sz;
			int x=rt,y=0;
			while(x)
			{
				if(val==t[x].val)
				{
					++t[x].num;
					pushup(x);
					return;
				}
				y=x;
				x=t[x].c[val>t[x].val];
			}
			x=++tcnt;
			t[x].num=t[x].sz=1;
			t[x].val=val;
			t[x].w=rand();
			if(y)
			{
				t[x].fa=y;
				t[y].c[val>t[y].val]=x;
				while(t[x].w<t[t[x].fa].w) rot(x);
				pushup(x);
			}
			else rt=x;
		}
		void erase(int val)
		{
			int x=find(val);
			if(!x) return;
			if(t[x].num>1)
			{
				--t[x].num;
				pushup(x);
				return;
			}
			while(t[x].c[0]||t[x].c[1])
			{
				if(t[x].c[0]&&t[x].c[1])
					rot(t[x].c[t[t[x].c[1]].w<t[t[x].c[0]].w]);
				else rot(t[x].c[0]|t[x].c[1]);
			}
			t[t[x].fa].c[t[t[x].fa].c[1]==x]=0;
			pushup(x);
			if(--sz==0) rt=0;
		}
		int lower(int val)
		{
			int x=rt,y=0;
			while(x)
			{
				if(t[x].val<val)
					y=x,x=t[x].c[1];
				else x=t[x].c[0];
			}
			return t[y].val;
		}
		int upper(int val)
		{
			int x=rt,y=0;
			while(x)
			{
				if(t[x].val>val)
					y=x,x=t[x].c[0];
				else x=t[x].c[1];
			}
			return t[y].val;
		}
		int n2r(int val)
		{
			int x=rt,res=1;
			while(x)
			{
				if(t[x].val<val)
				{
					res+=t[t[x].c[0]].sz+t[x].num;
					x=t[x].c[1];
				}
				else x=t[x].c[0];
			}
			return res;
		}
		int r2n(int k)
		{
			int x=rt;
			while(k<=t[t[x].c[0]].sz||t[t[x].c[0]].sz+t[x].num<k)
			{
				if(k<=t[t[x].c[0]].sz)
					x=t[x].c[0];
				else
				{
					k-=t[t[x].c[0]].sz+t[x].num;
					x=t[x].c[1];
				}
			}
			return t[x].val;
		}
} treap;

int main()
{
    int n;scanf("%d",&n);
    while(n--)
    {
        int opt,x;scanf("%d%d",&opt,&x);
        if(opt==1) treap.insert(x);
        else if(opt==2) treap.erase(x);
        else if(opt==3) printf("%d\n",treap.n2r(x));
        else if(opt==4) printf("%d\n",treap.r2n(x));
        else if(opt==5) printf("%d\n",treap.lower(x));
        else if(opt==6) printf("%d\n",treap.upper(x));
    }
    return 0; 
}
