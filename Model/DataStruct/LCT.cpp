#include<iostream>
#include<cstdio>
const int MAXN=3e5+5,INF=~0U>>1;
int n,m;
struct N
{
	int val,c[2],fa,sum,mx,det,sz;bool rev;
} t[MAXN];
int q[MAXN],tp;
void add(int x,int v)
{t[x].val+=v;t[x].sum+=v*t[x].sz;t[x].mx+=v;t[x].det+=v;}
void upd(int x)
{
	int lc=t[x].c[0],rc=t[x].c[1];
	t[x].sum=t[lc].sum+t[rc].sum+t[x].val;
	t[x].sz=t[lc].sz+t[rc].sz+1;
	t[x].mx=std::max(std::max(t[lc].mx,t[rc].mx),t[x].val);
}
void pushdown(int x)
{
	if(t[x].rev){t[t[x].c[0]].rev^=1;t[t[x].c[1]].rev^=1;t[x].rev^=1;swap(t[x].c[0],t[x].c[1]);}
	if(t[x].det) add(t[x].c[0],t[x].det),add(t[x].c[1],t[x].det),t[x].det=0;
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

void link(int x,int y){makeroot(y);t[y].fa=x;}

int read()
{
	int flag=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')flag=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return flag*x;
}

int main()
{
	n=read();m=read();
	t[0].mx=-INF;
	for(int i=1;i<=n;i++) add(i,read()),t[x].sz=1;
	while(m--)
	{
		int opt=read(),x=read(),y=read();
		if(opt==1) link(x,y);
		else if(opt==2) cut(x,y);
		else if(opt==3) splay(x),t[x].val=y,upd(x);
		else if(opt==4) split(x,y),printf("%d\n",t[x].mx);
		else if(opt==5) split(x,y),printf("%d\n",t[x].sum);
		else if(opt==6) printf("%d\n",findRt(x)==findRt(y));
		else if(opt==7) split(x,y),add(x,read());
	}
	return 0;
}
