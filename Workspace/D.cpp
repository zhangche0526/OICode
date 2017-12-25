#include<iostream>
#include<cstdio>
typedef long long ll;
const int P=998244353;
int qpow(int a,ll x)
{
    int res=1;
    for(;x;x>>=1,a=(ll)a*a%P)
        if(x&1) res=(ll)res*a%P;
    return res;
}
int exgcd(int a,int b,int &x,int &y)
{
    if(!b) {x=1,y=0;return a;}
    int res=exgcd(b,a%b,y,x);y-=a/b*x;return res;
}
int cinv(int a)
{
    int x,y;
    exgcd(a,P,x,y);
    return (x+P)%P;
}

class NTT
{
private:
    static const int MAXN=1e6+5,g=3;
    int pos[MAXN],n,m;
    int a[MAXN],b[MAXN];
    void trans(int *A,int ty)
    {
        int i,j,k;
        for(i=1;i<n;i++) if(i<pos[i])
            std::swap(A[i],A[pos[i]]);
        for(i=1;i<n;i<<=1)
        {
            int wn=qpow(g,(P-1)/(i<<1));
            if(ty) wn=cinv(wn);
            for(j=0;j<n;j+=i<<1)
            {
                int w=1;
                for(k=0;k<i;k++,w=(ll)w*wn%P)
                {
                    int x=A[j+k],y=(ll)A[i+j+k]*w%P;
                    A[j+k]=(x+y)%P,A[i+j+k]=(x+P-y)%P;
                }
            }
        }
    }
public:
    void mul(int *A,int AI,int *B,int BI,int *ans)
    {
        int i;
        for(i=0;i<=AI;i++) a[i]=A[i];
        for(i=0;i<=BI;i++) b[i]=B[i];
        m=AI+BI;int bL=0;for(n=1;n<=m;n<<=1) ++bL;
        for(i=1;i<n;i++) pos[i]=(pos[i>>1]>>1)|((i&1)<<(bL-1));

        trans(a,0);trans(b,0);
        for(i=0;i<n;i++) a[i]=(ll)a[i]*b[i]%P;
        trans(a,1);

        int nInv=cinv(n);
        for(i=0;i<=m;i++) ans[i]=(ll)a[i]*nInv%P;
    }
} ntt;

const int MAXK=2e5+5;

int fac[MAXK],inv[MAXK],facInv[MAXK];
int f[MAXK],g[MAXK],S2[MAXK],C[MAXK];
void preTab(int n,int k)
{
	int i;
	for(fac[0]=i=1;i<=k;i++) fac[i]=(ll)fac[i-1]*i%P;
	for(inv[1]=1,i=2;i<=k;i++) inv[i]=(ll)(P-P/i)*inv[P%i]%P;
	for(facInv[0]=i=1;i<=k;i++) facInv[i]=(ll)facInv[i-1]*inv[i]%P;
	for(i=0;i<=k;i++) {f[i]=facInv[i];if(i&1) f[i]=(P-f[i])%P;}
	for(i=0;i<=k;i++) g[i]=(ll)qpow(i,k)*facInv[i]%P;

	ntt.mul(f,k,g,k,S2);

	for(C[0]=i=1;i<=k;i++) C[i]=(ll)C[i-1]*(n-i)%P*inv[i]%P;
}

int solve(int n,int k)
{
	preTab(n,k);
	int ans=(ll)n*qpow(2,(ll)(n-1)*(n-2)>>1)%P;
	int sum=0;
	for(int i=1;i<=k;i++)
	{
		int res=(ll)S2[i]*fac[i]%P*C[i]%P*qpow(2,n-1-i)%P;
		sum=(sum+res)%P;
	}
	ans=(ll)ans*sum%P;
	return ans;
}

int main()
{
	int n,k;scanf("%d%d",&n,&k);
	printf("%d",solve(n,k));
	return 0;
}
