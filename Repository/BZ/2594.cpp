#include<iostream>
#include<cstdio>
#include<algorithm>
inline int read();
const int MAXN=1e5+5,MAXM=1e6+5,MAXQ=1e5+5;

int N,M,Q;

struct E{int u,v,w,id;bool deld;} e[MAXM];
bool cmpuv(const E &a,const E &b){return a.u<b.u||(a.u==b.u&&a.v<b.v);}
bool cmpw(const E &a,const E &b){return a.w<b.w;}
bool cmpid(const E &a,const E &b){return a.id<b.id;}

int find(E tgt)
{
	int l=1,r=M,mid;
	while(l<=r)
	{
		mid=l+r>>1;
		if(e[mid].u==tgt.u&&e[mid].v==tgt.v) return mid;
		if(e[mid].u<tgt.u||(e[mid].u==tgt.u&&e[mid].v<tgt.v)) l=mid+1;
		else r=mid-1;
	}
	return 0;
}

struct QRY{int typ,u,v,ans,id;} q[MAXQ];

int fa[MAXN];
inline void initUFS(){for(int i=1;i<=N;i++) fa[i]=i;}
int findAnc(int x){return fa[x]==x?x:fa[x]=findAnc(fa[x]);}

struct LCTN
{
    int val,c[2],fa,mx,sz;bool rev;
} t[MAXN+MAXM];
 
void upd(int x)
{
	t[x].sz=t[t[x].c[0]].sz+t[t[x].c[1]].sz+1;
	t[x].mx=x;
	if(t[t[t[x].c[0]].mx].val>t[t[x].mx].val)
		t[x].mx=t[t[x].c[0]].mx;
	if(t[t[t[x].c[1]].mx].val>t[t[x].mx].val)
		t[x].mx=t[t[x].c[1]].mx;
}

void pushdown(int x)
{
    if(t[x].rev)
    {
        t[t[x].c[0]].rev^=1;t[t[x].c[1]].rev^=1;
        t[x].rev^=1;std::swap(t[x].c[0],t[x].c[1]);
    }
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
  
void makeRt(int x){access(x);splay(x);t[x].rev^=1;}

void split(int x,int y){makeRt(x);access(y);splay(y);}

void cut(int x,int y){split(x,y);t[y].c[0]=t[x].fa=0;}
  
void link(int x,int y){makeRt(y);t[y].fa=x;}

int main()
{
	int i;
	N=read();M=read();Q=read();
	for(i=1;i<=M;i++)
	{
		e[i].u=read();e[i].v=read();e[i].w=read();
		if(e[i].u>e[i].v) std::swap(e[i].u,e[i].v);
	}
	std::sort(e+1,e+M+1,cmpw);
	for(i=1;i<=M;i++)
	{
		e[i].id=i;
		t[N+i].val=e[i].w;
		t[N+i].mx=N+i;
	}
	std::sort(e+1,e+M+1,cmpuv);
	for(i=1;i<=Q;i++)
	{
		q[i].typ=read();q[i].u=read();q[i].v=read();
		if(q[i].u>q[i].v) std::swap(q[i].u,q[i].v);
		if(q[i].typ==2)
		{
			int pos=find((E){q[i].u,q[i].v});
			e[pos].deld=true;q[i].id=e[pos].id;
		}
	}
	std::sort(e+1,e+M+1,cmpw);
	int tot=0;initUFS();
	for(i=1;i<=M;i++)
		if(!e[i].deld)
			if(findAnc(e[i].u)!=findAnc(e[i].v))
			{
				fa[findAnc(e[i].u)]=findAnc(e[i].v);
				link(i+N,e[i].u);link(i+N,e[i].v);
				tot++;
				if(tot==N-1) break;
			}
	for(i=Q;i;i--)
	{
		split(q[i].u,q[i].v);int pos=t[q[i].v].mx;
		if(q[i].typ==1) q[i].ans=t[pos].val;
		else
		{
			if(e[q[i].id].w<t[pos].val)
			{
				cut(pos,e[pos-N].u);cut(pos,e[pos-N].v);
				link(q[i].id+N,q[i].u);link(q[i].id+N,q[i].v);
			}
		}
	}
	for(i=1;i<=Q;i++) if(q[i].typ==1)
		printf("%d\n",q[i].ans);
	return 0;
}

inline int read()
{
	int res=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') res=res*10+c-'0',c=getchar();
	return res;
}
