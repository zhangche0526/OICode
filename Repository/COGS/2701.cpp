#include<iostream>
#include<cstdio>
const int MAXN=2e5+5,INF=~0U>>1;
int n,m;
struct N
{
	int val,c[2],fa,sum,mx,det,sz,vir;bool rev;
} t[MAXN];
void upd(int x)
{t[x].sz=t[t[x].c[0]].sz+t[t[x].c[1]].sz+t[x].vir+1;}
void pushdown(int x)
{if(t[x].rev){t[t[x].c[0]].rev^=1;t[t[x].c[1]].rev^=1;t[x].rev^=1;std::swap(t[x].c[0],t[x].c[1]);}}

inline bool isRt(int x){return t[t[x].fa].c[0]!=x&&t[t[x].fa].c[1]!=x;}
inline bool iden(int x){return t[t[x].fa].c[1]==x;}
void rot(int x)
{
	int y=t[x].fa,z=t[y].fa;
	pushdown(y);pushdown(x);
	bool xT=iden(x),yT=iden(y);
	if(!isRt(y)) t[z].c[yT]=x;t[x].fa=z;
	t[y].fa=x;t[t[x].c[!xT]].fa=y;
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
void access(int x)
{
	for(int y=0;x;y=x,x=t[x].fa) 
	{
		splay(x);
		t[x].vir-=t[y].sz;
		t[x].vir+=t[t[x].c[1]].sz;
		t[x].c[1]=y;
		upd(x);
	}
}
void makeRt(int x){access(x);splay(x);t[x].rev^=1;}

int findRt(int x){access(x);splay(x);while(t[x].c[0]) x=t[x].c[0];return x;}

void link(int x,int y){makeRt(y);t[y].fa=x;t[x].vir+=t[y].sz;}


int read()
{
	int flag=1,x=0;char ch;
	do{ch=getchar();if(ch=='-')flag=-1;}while(ch<'0'||ch>'9');
	do{x=x*10+ch-'0';ch=getchar();}while(ch>='0'&&ch<='9');
	return flag*x;
}
int main()
{
	freopen("dynamic_tree.in","r",stdin);
	freopen("dynamic_tree.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++) t[i].sz=1;
	while(m--)
	{
		int opt=read(),u=read();
		if(opt==1) makeRt(u);
		else if(opt==2) access(u),printf("%d\n",t[u].vir+1);
		else if(opt==3) 
		{int uRt=findRt(u);link(u,read());makeRt(uRt);}
	}
	return 0;
}
