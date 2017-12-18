#include<iostream>
#include<cstdio>
#include<algorithm>
using std::min;
using std::max;
typedef long long ll;
const int MAXN=5e4+5;

int n;

struct Tri
{
	int a,b,c,*f;
	Tri(){}
	Tri(int a,int b,int c,int *f):a(a),b(b),c(c),f(f){}
} itm[MAXN];
bool cmpa(const Tri &x,const Tri &y){return x.a<y.a;}
bool cmpb(const Tri &x,const Tri &y){return x.b<y.b;}

int f[MAXN];

void mkData(int a,int p)
{
	int i;
	static int ap[MAXN*3];
	for(ap[0]=i=1;i<=3*n;i++) ap[i]=(ll)ap[i-1]*a%p;
	for(i=1;i<=n;i++)
	{
		int tmp[3];
		tmp[0]=ap[i*3-2],tmp[1]=ap[i*3-1],tmp[2]=ap[i*3];
		std::sort(tmp,tmp+3);
		itm[i]=Tri(tmp[0],tmp[1],tmp[2],&f[i]);
	}
}

inline void discrt()
{
	int i;
	static int rsp[MAXN];int rcnt;
	for(i=1;i<=n;i++) rsp[i]=itm[i].c;
	std::sort(rsp+1,rsp+n+1);
	rcnt=std::unique(rsp+1,rsp+n+1)-(rsp+1);
	for(i=1;i<=n;i++) itm[i].c=std::lower_bound(rsp+1,rsp+rcnt+1,itm[i].c)-rsp;
}

struct FT
{
	int na[MAXN];
	void umx(int x,int v){for(;x<=n;x+=x&(-x)) na[x]=max(na[x],v);}
	int cmx(int x){int res=0;for(;x;x-=x&(-x)) res=max(res,na[x]);return res;}
	void clean(int x){for(;x<=n;x+=x&(-x)) if(na[x]) na[x]=0;else return;}
} ft;

int dvd(int l,int r)
{
	int mid=(l+r)>>1;
	while(mid<r&&itm[mid].a==itm[mid+1].a) mid++;
	if(mid<r) return mid;
	mid=(l+r)>>1;
	while(mid>l&&itm[mid].a==itm[mid-1].a) mid--;
	if(mid>l) return mid;
	return 0;
}

Tri tmp[MAXN];
void cdq(int l,int r)
{
	if(l==r) return;
	int i,mid=dvd(l,r);
	if(!mid) return;
	cdq(l,mid);
	std::sort(itm+l,itm+mid+1,cmpb);
	std::sort(itm+mid+1,itm+r+1,cmpb);
	int p1=l,p2=mid+1;
	for(i=l;i<=r;i++)
	{
		if(p2>r||(p1<=mid&&itm[p1].b<=itm[p2].b))
		{ft.umx(itm[p1].c,*itm[p1].f+1);p1++;}
		else{*itm[p2].f=max(*itm[p2].f,ft.cmx(itm[p2].c-1));p2++;}
	}
	for(i=l;i<=mid;i++) ft.clean(itm[i].c);
	std::sort(itm+mid+1,itm+r+1,cmpa);
	cdq(mid+1,r);
}

int main()
{
	int i;
	int a,p;scanf("%d%d%d",&a,&p,&n);
	mkData(a,p);
	discrt();
	std::sort(itm+1,itm+n+1,cmpa);
	cdq(1,n);
	int ans=0;
	for(i=1;i<=n;i++) ans=max(ans,f[i]+1);
	printf("%d",ans);
	return 0;
}
