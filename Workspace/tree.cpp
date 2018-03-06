#include<iostream>
#include<cstdio>
typedef unsigned uint;

const int MAXN=1e5+5,P=51061;

struct LCTN
{
	int c[2],fa,rev,sz,val,sum,det,mul;
} t[MAXN];
inline void upd(int x)
{
	LCTN &lc=t[t[x].c[0]],&rc=t[t[x].c[1]];
	t[x].sz=lc.sz+rc.sz;
	t[x].sum=(lc.sz+rc.sz+t[x].val)%P;
}

inline void apply(int x,int d,int m,int r)
{
	t[x].val=((uint)t[x].val*m+d)%P;
	t[x].sum=((uint)t[x].sum*m+d*t[x].sz)%P;
	t[x].det=((uint)t[x].det*m+d)%P;
	t[x].mul=((uint)t[x].mul*m)%P;
	if(r) std::swap(t[x].c[0],t[x].c[1]);
}
inline void pushdown(int x)
{
	apply(t[x].c[0],t[x].det,t[x].mul,t[x].rev);
	apply(t[x].c[1],t[x].det,t[x].mul,t[x].rev);
	t[x].det=0,t[x].mul=1,t[x].rev=0;
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
 
void makeroot(int x){access(x);splay(x);t[x].rev^=1;}
 
int findRt(int x){access(x);splay(x);while(t[x].c[0]) x=t[x].c[0];return x;}
 
void split(int x,int y){makeroot(x);access(y);splay(y);}
 
void cut(int x,int y){split(x,y);if(t[y].c[0]==x) t[y].c[0]=0,t[x].fa=0;}
 
void link(int x,int y){makeroot(x);t[x].fa=y;}

int n,q;

int main()
{
	int i;scanf("%d%d",&n,&q);
	for(i=1;i<=n;i++) t[i].sz=t[i].val=t[i].sum=t[i].mul=1;
	for(i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		link(u,v);
	}
	while(q--)
	{
		char opt[10];scanf("%s",opt);
		if(opt[0]=='+'||opt[0]=='*')
		{
			int u,v,c;scanf("%d%d%d",&u,&v,&c);
			split(v,u);
			if(opt[0]=='+') apply(u,c,1,0);
			else apply(u,0,c,0);
		}
		else if(opt[0]=='-')
		{
			int u1,v1,u2,v2;scanf("%d%d%d%d",&u1,&v1,&u2,&v2);
			cut(u1,v1);
			link(u2,v2);
		}else
		{
			int u,v;scanf("%d%d",&u,&v);
			split(v,u);
			printf("%d\n",t[u].sum);
		}
	}
	return 0;
}
