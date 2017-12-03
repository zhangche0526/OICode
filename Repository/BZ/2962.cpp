#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
using std::max;
typedef long long ll;
const int MAXN=5e4+5,P=19940417;

int N,Q;

int na[MAXN];

int C[MAXN][21];
inline void initC()
{
	int i,j;C[0][0]=1;
	for(i=1;i<=N;i++)
	{
		C[i][0]=1;
		for(j=1;j<=min(i,20);j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
	}
}

struct S{int len,f[21];S(){memset(f,0,sizeof(f));len=0;}};

const int rt=1;
struct SEGTN{int l,r,lc,rc;bool rev;int det;S stt;} t[MAXN<<1];int tcnt=rt;

S mrg(S a,S b)
{
	int i,j;S res;res.len=min(20,a.len+b.len);
	for(i=0;i<=a.len;i++)
		for(j=0;j<=b.len&&i+j<=20;j++)
			res.f[i+j]=(res.f[i+j]+(ll)a.f[i]*b.f[j]%P)%P;
	return res;
}

inline void updRev(int o)
{
	int i;t[o].rev^=1;t[o].det=(P-t[o].det)%P;
	for(i=0;i<=t[o].stt.len;i++)
		if(i&1) t[o].stt.f[i]=(P-t[o].stt.f[i])%P;
}

inline void updDet(int o,int v)
{
	int i,j,prd;t[o].det=(t[o].det+v)%P;
	for(i=t[o].stt.len;i>=0;i--)
		for(prd=v,j=i-1;j>=0;j--,prd=(ll)prd*v%P)
			t[o].stt.f[i]=(t[o].stt.f[i]+(ll)t[o].stt.f[j]*C[t[o].r-t[o].l+1-j][i-j]%P*prd%P)%P;
}

void pushdown(int o)
{
	if(t[o].rev) {updRev(t[o].lc);updRev(t[o].rc);t[o].rev=false;}
	if(t[o].det) {updDet(t[o].lc,t[o].det);updDet(t[o].rc,t[o].det);t[o].det=0;}
}

void buildTree(int o,int l,int r)
{
	t[o].l=l,t[o].r=r;
	if(l==r) {t[o].stt.f[0]=1;t[o].stt.f[1]=na[l];t[o].stt.len=1;return;}
	int mid=(l+r)>>1;
	t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
	t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
	t[o].stt=mrg(t[t[o].lc].stt,t[t[o].rc].stt);
}

void chDet(int o,int l,int r,int v)
{
	if(l<=t[o].l&&t[o].r<=r) {updDet(o,v);return;}
	int mid=(t[o].l+t[o].r)>>1;
	pushdown(o);
	if(l<=mid) chDet(t[o].lc,l,r,v);
	if(r>mid) chDet(t[o].rc,l,r,v);
	t[o].stt=mrg(t[t[o].lc].stt,t[t[o].rc].stt);
}

void chRev(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) {updRev(o);return;}
	int mid=(t[o].l+t[o].r)>>1;
	pushdown(o);
	if(l<=mid) chRev(t[o].lc,l,r);
	if(r>mid) chRev(t[o].rc,l,r);
	t[o].stt=mrg(t[t[o].lc].stt,t[t[o].rc].stt);
}

S calF(int o,int l,int r)
{
	if(l<=t[o].l&&t[o].r<=r) return t[o].stt;
	int mid=(t[o].l+t[o].r)>>1;
	pushdown(o);
	if(l<=mid&&r>mid) return mrg(calF(t[o].lc,l,r),calF(t[o].rc,l,r));
	if(l<=mid) return calF(t[o].lc,l,r);
	return calF(t[o].rc,l,r);
}

int main()
{
	int i;
	scanf("%d%d",&N,&Q);initC();
	for(i=1;i<=N;i++) scanf("%d",na+i),na[i]%=P;
	buildTree(rt,1,N);
	while(Q--)
	{
		char opt[10];int l,r,v;
		scanf("%s",opt);
		scanf("%d%d",&l,&r);
		if(opt[0]!='R') scanf("%d",&v);
		switch(opt[0])
		{
			case 'I':chDet(rt,l,r,(v+P)%P);break;
			case 'R':chRev(rt,l,r);break;
			case 'Q':printf("%d\n",calF(rt,l,r).f[v]);break;
		}
	}
	return 0;
}

