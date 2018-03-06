#include<iostream>
#include<cstdio>
using namespace std;
const int MAXN=3e5+5;
int n,m;
struct N
{
	int val,c[2],fa,xr,rev;
} t[MAXN];
int q[MAXN],tp;
inline void upd(int x){t[x].xr=t[t[x].c[0]].xr^t[t[x].c[1]].xr^t[x].val;}
inline void pushdown(int x)
{if(t[x].rev){t[t[x].c[0]].rev^=1;t[t[x].c[1]].rev^=1;t[x].rev^=1;swap(t[x].c[0],t[x].c[1]);}}

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

inline int read()
{
	int f=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return f*x;
}
int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) t[i].xr=t[i].val=read();
	while(m--)
	{
		int opt=read(),x=read(),y=read();
		if(opt==0){split(x,y);printf("%d\n",t[y].xr);}
		else if(opt==1){if(findRt(x)!=findRt(y)) link(x,y);}
		if(opt==2){if(findRt(x)==findRt(y)) cut(x,y);}
		if(opt==3){access(x);splay(x);t[x].val=y;upd(x);}
	}
	return 0;
}
