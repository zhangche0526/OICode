#include<iostream>
#include<cstdio>
#include<algorithm>
typedef long long ll;
const int MAXN=132005,MAXK=5e4+5,P=1e9+7,M[3]={998244353,1004535809,469762049};
const ll M01=(ll)M[0]*M[1];

int qpow(int a,int x,int p)
{
	int res=1;
	for(;x;x>>=1,a=(ll)a*a%p)
		if(x&1) res=(ll)res*a%p;
	return res;
}
ll qmul(ll a,ll x,ll p)
{
	ll res=0;
	for(;x;x>>=1,a=(a+a)%p)
		if(x&1) res=(res+a)%p;
	return res;
}
int exgcd(int a,int b,int &x,int &y)
{
	if(!b) {x=1,y=0;return a;}
	int res=exgcd(b,a%b,y,x);y-=a/b*x;return res;
}
int inv(int a,int p)
{
	int x,y;
	exgcd(a,p,x,y);
	return (x+p)%p;
}
int CRT(int a0,int a1,int a2)
{
	ll A=(qmul( (ll)a0*M[1]%M01, inv(M[1],M[0]), M01)+qmul( (ll)a1*M[0]%M01, inv(M[0],M[1]), M01))%M01;
	int k=(ll)(a2+M[2]-A%M[2])*inv(int(M01%M[2]),M[2])%M[2];
	return ((ll)k*(M01%P)%P+A)%P;
}

int pos[MAXN],bb[3][MAXN];
void trans(int *A,int n,int p,bool ty)
{
	int i,j,k;
	for(i=1;i<n;i++) if(i<pos[i])
		std::swap(A[i],A[pos[i]]);
	for(i=1;i<n;i<<=1)
	{
		int wn=qpow(3,(p-1)/(i<<1),p);
		if(ty) wn=inv(wn,p);
		for(j=0;j<n;j+=i<<1)
		{
			int w=1;
			for(k=0;k<i;k++,w=(ll)w*wn%p)
			{
				int x=A[j+k],y=(ll)A[i+j+k]*w%p;
				A[j+k]=(x+y)%p,A[i+j+k]=(x+p-y)%p;
			}
		}
	}
}

int a[MAXN],b[MAXN],tmp[MAXN];
void polyInv(int m)
{
	if(m==1) {b[0]=CRT(inv(a[0],M[0]),inv(a[0],M[1]),inv(a[0],M[2]));return;}
	polyInv((m+1)>>1);

	int i,t,n,bL=0;for(n=1;n<m<<1;n<<=1) ++bL;
	for(i=1;i<n;i++) pos[i]=(pos[i>>1]>>1)|((i&1)<<(bL-1));
	for(t=0;t<3;t++)
	{
		std::copy(b,b+m,bb[t]);
		std::fill(bb[t]+m,bb[t]+n,0);
		std::copy(a,a+m,tmp);
		std::fill(tmp+m,tmp+n,0);

		trans(tmp,n,M[t],0);trans(bb[t],n,M[t],0);
		for(i=0;i<n;i++) bb[t][i]=(ll)bb[t][i]*tmp[i]%M[t];
		trans(bb[t],n,M[t],1);

		int nInv=inv(n,M[t]);
		for(i=0;i<m;i++) bb[t][i]=(ll)bb[t][i]*nInv%M[t];
	}
	for(i=0;i<m;i++)
	{
		int res=CRT(bb[0][i],bb[1][i],bb[2][i]);
		bb[0][i]=bb[1][i]=bb[2][i]=res?P-res:0;
	}
	bb[0][0]=bb[1][0]=bb[2][0]=((ll)bb[0][0]+2)%P;
	for(t=0;t<3;t++)
	{
		std::copy(b,b+m,tmp);
		std::fill(tmp+m,tmp+n,0);

		trans(tmp,n,M[t],0);trans(bb[t],n,M[t],0);
		for(i=0;i<n;i++) bb[t][i]=(ll)bb[t][i]*tmp[i]%M[t];
		trans(bb[t],n,M[t],1);

		int nInv=inv(n,M[t]);
		for(i=0;i<m;i++) bb[t][i]=(ll)bb[t][i]*nInv%M[t];
	}
	for(i=0;i<m;i++) b[i]=CRT(bb[0][i],bb[1][i],bb[2][i]);
}
void polyInv(int *A,int Adgr,int *B)
{
	int m=Adgr+1;
	std::copy(A,A+m,a);
	polyInv(m);
	std::copy(b,b+m,B);
}
int fac[MAXK],facInv[MAXK];

int C(int n,int k){return (ll)fac[n]*facInv[k]%P*facInv[n-k]%P;}

int na[MAXK],ans[MAXK];
int B[MAXK];
void preTab()
{
	int i;
	for(fac[0]=i=1;i<MAXK;i++) fac[i]=(ll)fac[i-1]*i%P;
	for(facInv[1]=1,i=2;i<MAXK;i++) facInv[i]=(ll)(P-P/i)*facInv[P%i]%P;
	for(facInv[0]=i=1;i<MAXK;i++) facInv[i]=(ll)facInv[i-1]*facInv[i]%P;
	for(i=0;i<=50000;i++) na[i]=facInv[i+1];
	polyInv(na,50000,ans);
	for(i=0;i<=50000;i++) B[i]=(ll)ans[i]*fac[i]%P;	
}

int np[MAXK];
int calc(int n,int k)
{
	int i,res=0;
	for(np[0]=i=1;i<=k+1;i++) np[i]=(ll)np[i-1]*(n+1)%P;
	for(i=1;i<=k+1;i++) res=(res+(ll)C(k+1,i)*B[k+1-i]%P*np[i]%P)%P;
	return (ll)res*inv(k+1,P)%P;
}

int main()
{
	preTab();
	int T;scanf("%d",&T);
	while(T--)
	{
		ll n;int k;scanf("%lld%d",&n,&k);
		printf("%d\n",calc(n%P,k));
	}
	return 0;
}

