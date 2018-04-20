#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
typedef long long ll;

const int MAXN=1e5+5,INF=1061109567;

int n,q;
int na[MAXN];

int st[MAXN][20];
inline void initST()
{
	int i,k;
	for(i=1;i<=n;i++) st[i][0]=i;
	for(k=1;k<=log2(n);k++)
		for(i=1;i+(1<<k)-1<=n;i++)
			st[i][k]=na[st[i][k-1]]<na[st[i+(1<<k-1)][k-1]]?st[i][k-1]:st[i+(1<<k-1)][k-1];
}
inline int cmnp(int l,int r)
{
	int k=log2(r-l+1);
	return na[st[l][k]]<na[st[r-(1<<k)+1][k]]?st[l][k]:st[r-(1<<k)+1][k];
}

ll fl[MAXN],fr[MAXN];
inline void dp(ll *f)
{
	static int st[MAXN],tp;
	st[tp=1]=0;
	for(int i=1;i<=n;i++)
	{
		while(na[st[tp]]>na[i]) tp--;
		f[i]=f[st[tp]]+(ll)(i-st[tp])*na[i];
		st[++tp]=i;
	}
}

int bsz,blg[MAXN];
struct Q{int l,r,id;} qry[MAXN];
bool operator <(const Q &a,const Q &b)
{return blg[a.l]<blg[b.l]||(blg[a.l]==blg[b.l]&&a.r<b.r);}

ll updR(int l,int r)
{
	int p=cmnp(l,r+1);
	return (ll)(p-l+1)*na[p]+fl[r+1]-fl[p];
}

ll updL(int l,int r)
{
	int p=cmnp(l-1,r);
	return (ll)(r-p+1)*na[p]+fr[l-1]-fr[p];
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("my.out","w",stdout);
#endif
	int i;scanf("%d%d",&n,&q);na[0]=-INF;
	for(i=1;i<=n;i++) scanf("%d",na+i);
	bsz=sqrt(n);
	for(i=1;i<=n;i++) blg[i]=i/bsz+1;
	initST();
	dp(fl);std::reverse(na+1,na+n+1);
	dp(fr);std::reverse(na+1,na+n+1);std::reverse(fr+1,fr+n+1);
	for(i=1;i<=q;i++) 
	{
		int l,r;scanf("%d%d",&l,&r);
		qry[i]=(Q){l,r,i};
	}
	std::sort(qry+1,qry+q+1);
	static ll ans[MAXN];
	int l=1,r=0;ll res=0;
	for(i=1;i<=q;i++)
	{
		while(r<qry[i].r) res+=updR(l,r++);
		while(r>qry[i].r) res-=updR(l,--r);
		while(l>qry[i].l) res+=updL(l--,r);
		while(l<qry[i].l) res-=updL(++l,r);
		ans[qry[i].id]=res;
	}
	for(i=1;i<=q;i++) printf("%lld\n",ans[i]);
	return 0;
}
