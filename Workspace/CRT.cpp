#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=262200,m1=998244353,m2=1004535809,m3=469762049,g=3,Mod=1e9+7;
const long long M=(long long)m1*m2;
void NTT(int*,int,int,int);
int China(int,int,int);
int qpow(int,int,int);
long long mul(long long,long long,long long);
int n,N=1,A[maxn],B[maxn],C[maxn],D[maxn],a[3][maxn];
int main(){
	/*
    freopen("annona_squamosa.in","r",stdin);
    freopen("annona_squamosa.out","w",stdout);
    scanf("%d",&n);
    while(N<(n<<1))N<<=1;
    for(int i=0;i<n;i++)scanf("%d",&A[i]);
    for(int i=0;i<n;i++)scanf("%d",&B[i]);
    copy(A,A+N,C);
    copy(B,B+N,D);
    NTT(C,N,1,m1);
    NTT(D,N,1,m1);
    for(int i=0;i<N;i++)a[0][i]=(long long)C[i]*D[i]%m1;
    NTT(a[0],N,-1,m1);
    copy(A,A+N,C);
    copy(B,B+N,D);
    NTT(C,N,1,m2);
    NTT(D,N,1,m2);
    for(int i=0;i<N;i++)a[1][i]=(long long)C[i]*D[i]%m2;
    NTT(a[1],N,-1,m2);
    copy(A,A+N,C);
    copy(B,B+N,D);
    NTT(C,N,1,m3);
    NTT(D,N,1,m3);
    for(int i=0;i<N;i++)a[2][i]=(long long)C[i]*D[i]%m3;
    NTT(a[2],N,-1,m3);*/
    printf("%d\n%d",China(m1-qpow(2,m1-2,m1),m2-qpow(2,m2-2,m2),m3-qpow(2,m3-2,m3)),Mod-qpow(2,Mod-2,Mod));
    //for(int i=0;i<n;i++)printf("%d\n",China(a[0][i],a[1][i],a[2][i]));
    return 0;
}
void NTT(int *A,int n,int tp,int p){
    for(int i=0;i<n;i++)A[i]%=p;
    for(int i=1,j=0,k;i<n-1;i++){
        k=n;
        do j^=(k>>=1);while(j<k);
        if(i<j)swap(A[i],A[j]);
    }
    for(int k=2;k<=n;k<<=1){
        int wn=qpow(g,(tp>0?(p-1)/k:(p-1)/k*(long long)(p-2)%(p-1)),p);
        for(int i=0;i<n;i+=k){
            int w=1;
            for(int j=0;j<(k>>1);j++,w=(long long)w*wn%p){
                int a=A[i+j],b=(long long)w*A[i+j+(k>>1)]%p;
                A[i+j]=(a+b)%p;
                A[i+j+(k>>1)]=(a-b+p)%p;
            }
        }
    }
    if(tp<0){
        int inv=qpow(n,p-2,p);
        for(int i=0;i<n;i++)A[i]=(long long)A[i]*inv%p;
    }
}
int China(int a1,int a2,int a3){
    long long A=(mul((long long)a1*m2%M,qpow(m2%m1,m1-2,m1),M)+mul((long long)a2*m1%M,qpow(m1%m2,m2-2,m2),M))%M,k=((a3-A)%m3+m3)%m3*qpow(M%m3,m3-2,m3)%m3;
    return ((k%Mod)*(M%Mod)%Mod+A%Mod)%Mod;
}
int qpow(int a,int b,int p){
    int ans=1;
    for(;b;b>>=1,a=(long long)a*a%p)if(b&1)ans=(long long)ans*a%p;
    return ans;
}
long long mul(long long a,long long b,long long p){
    a%=p;b%=p;
    return ((a*b-(long long)((long long)((long double)a/p*b+1e-3)*p))%p+p)%p;
}
