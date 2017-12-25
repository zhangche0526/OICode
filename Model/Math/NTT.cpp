#include<iostream>
#include<cstdio>
typedef long long ll;
int qpow(int a,int x,int p)
{
    int res=1;
    for(;x;x>>=1,a=(ll)a*a%p)
        if(x&1) res=(ll)res*a%p;
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

class NTT
{
private:
    static const int MAXN=21e5+5,P=1004535809,g=3;
    int pos[MAXN],n,m;
    int a[MAXN],b[MAXN];
    void trans(int *A,int ty)
    {
        int i,j,k;
        for(i=1;i<n;i++) if(i<pos[i])
            std::swap(A[i],A[pos[i]]);
        for(i=1;i<n;i<<=1)
        {
            int wn=qpow(g,(P-1)/(i<<1),P);
            if(ty) wn=inv(wn,P);
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

        int nInv=inv(n,P);
        for(i=0;i<=m;i++) ans[i]=(ll)a[i]*nInv%P;
    }
} ntt;

const int MAXN=1e6+5;

int a[MAXN],b[MAXN],ans[MAXN<<1];
int main()
{
    int i,n,m;scanf("%d%d",&n,&m);
    for(i=0;i<=n;i++) scanf("%d",a+i);
    for(i=0;i<=m;i++) scanf("%d",b+i);
    ntt.mul(a,n,b,m,ans);
    for(i=0;i<=n+m;i++) printf("%d ",ans[i]);
}

