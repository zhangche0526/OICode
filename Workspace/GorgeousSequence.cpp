#include<iostream>
#include<cstdio>
using std::min;
using std::max;
template<typename T>
T read()
{
	T res=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') res=res*10+c-'0',c=getchar();
	return res;
}
template<typename T>
void write(T x)
{
	int i,L=-1;char s[20];
	while(x) s[++L]=x%10,x/=10;
	for(i=L;i>=0;i--) putchar(s[i]);
}

const int MAXN=1e6+5;

const int rt=1;int na[MAXN];
struct SEGTN{int l,r,lc,rc;int mx,cnt,nd;ll sum;} t[MAXN<<1];int tcnt;
inline void upd(int o)
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	t[o].sum=lc.sum+rc.sum;
	if(lc.mx<rc.mx) t[o].mx=lc.mx,t[o].cnt=lc.cnt,t[o].nd=rc.mx;
	else if(lc.mx>rc.mx) t[o].mx=rc.mx,t[o].cnt=rc.cnt,t[o].nd=lc.mx;
	else t[o].mx=lc.mx,t[o].cnt=lc.cnt+rc.cnt,t[o].nd=max(lc.nd,rc.nd);
}
inline void putTag(int o,int v){t[o].sum-=(ll)cnt*(t[o].mx-v),t[o].mx=v;}
inline void psd(int o)//fake push_down, no push_down actually
{
	SEGTN &lc=t[t[o].lc],&rc=t[t[o].rc];
	if(lc.mx>t[o].mx) putTag(t[o].lc,t[o].mx);
	if(rc.mx>t[o].mx) putTag(t[o].rc,t[o].mx);
}
void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) {t[o].mx=t[o].sum=na[l],t[o].cnt=1;return;}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	upd(o);
}

void ch(int o,int l,int r,int v)
{
	if(v<=t[o].mx) return;
	if(l<=t[o].l&&t[o].r<=r)
		if(v>t[o].nd) {putTag(o,v);return;}
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid) ch(t[o].lc,l,r,v);
	if(r>mid) ch(t[o].rc,l,r,v);
	upd(o);
}
ll calSum(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return calSum(t[o].lc,l,r)+calSum(t[o].rc,l,r);
	if(l<=mid) return calSum(t[o].lc,l,r);
	return calSum(t[o].rc,l,r);
}
int calMx(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].mx;
	psd(o);
	int mid=(t[o].l+t[o].r)>>1;
	if(l<=mid&&r>mid) return max(calMx(t[o].lc,l,r),calMx(t[o].rc,l,r));
	if(l<=mid) return calMx(t[o].lc,l,r);
	return calMx(t[o].rc,l,r);
}

int main()
{
	int T=read();
	while(T--)
	{
		int opt,x,y,t;opt=read();x=read();y=read();
		switch(opt)
		{
			case 0:t=read();mdf(x,y,read());break;
			case 1:write(qry1(x,y));puts();break;
			case 2:write(qry2(x,y));puts();break;
		}
	}
	return 0;
}
