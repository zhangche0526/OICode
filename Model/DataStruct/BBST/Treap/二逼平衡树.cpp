#include<cstdio>
#include<cstdlib>
#include<iostream>
using namespace std;

const int MAXN=5e4+5,INF=~0U>>1;

struct N
{
	int val;
    int fa,c[2];
    int num,sz;//出现次数
    int w;
} tp[MAXN*30];int tpcnt;
#define t tp
#define tcnt tpcnt
class TREAP
{
	private:
		int sz,rt;
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
			return y?t[y].val:-INF;
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
			return y?t[y].val:INF;
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
};
#undef t
#undef tcnt
int na[MAXN];
struct SEGTN
{
	int l,r,lc,rc;
	TREAP dat;
} t[MAXN<<1];int tcnt=1;const int rt=1;
void buildSEGT(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	for(int i=l;i<=r;i++) t[o].dat.insert(na[i]);	
	if(l==r) return;
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildSEGT(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildSEGT(t[o].rc,mid+1,r);
}
int calLowNum(int o,int l,int r,int val)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].dat.n2r(val)-1;
	int mid=(t[o].l+t[o].r)>>1;
	int res=0;
	if(l<=mid) res+=calLowNum(t[o].lc,l,r,val);
	if(r>mid) res+=calLowNum(t[o].rc,l,r,val);
	return res;
}
int getRbyN(int l,int r,int val)
{return calLowNum(rt,l,r,val)+1;}
int getNbyR(int l,int r,int rk)
{
	int L=0,R=(int)1e8,tmpRk,mid;
	while(L<=R)
	{
		mid=(L+R)>>1;
		tmpRk=calLowNum(rt,l,r,mid)+1;
		if(tmpRk>rk) R=mid-1;
		else L=mid+1;
	}
	return R;
}
void chCh(int o,int	pos,int val)
{
	t[o].dat.erase(na[pos]);
	t[o].dat.insert(val);
	if(t[o].l==t[o].r){na[pos]=val;return;}
	int mid=(t[o].l+t[o].r)>>1;
	if(pos<=mid) chCh(t[o].lc,pos,val);
	else if(pos>mid) chCh(t[o].rc,pos,val);
}
int calLower(int o,int l,int r,int val)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].dat.lower(val);
	int mid=(t[o].l+t[o].r)>>1;
	int res1=-INF,res2=-INF;
	if(l<=mid) res1=calLower(t[o].lc,l,r,val);
	if(r>mid) res2=calLower(t[o].rc,l,r,val);
	return max(res1,res2);
}
int calUpper(int o,int l,int r,int val)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].dat.upper(val);
	int mid=(t[o].l+t[o].r)>>1;
	int res1=INF,res2=INF;
	if(l<=mid) res1=calUpper(t[o].lc,l,r,val);
	if(r>mid) res2=calUpper(t[o].rc,l,r,val);
	return min(res1,res2);
}
int main()
{
	freopen("psh.in","r",stdin);
	freopen("psh.out","w",stdout);
    int i,n,m;scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) scanf("%d",&na[i]);
    buildSEGT(rt,1,n);
    while(m--)
    {
        int opt,l,r,pos,x;scanf("%d",&opt);
        if(opt==3) scanf("%d%d",&pos,&x);
		else scanf("%d%d%d",&l,&r,&x);
		if(opt==1) printf("%d\n",getRbyN(l,r,x));
		else if(opt==2) printf("%d\n",getNbyR(l,r,x));
		else if(opt==3) chCh(rt,pos,x);
		else if(opt==4) printf("%d\n",calLower(rt,l,r,x));
		else if(opt==5) printf("%d\n",calUpper(rt,l,r,x));
    }
    return 0; 
}
