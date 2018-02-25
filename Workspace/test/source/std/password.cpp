#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int mod=998244353;
struct mat {
    int a,b,c,d;
}ZR,E,F,Ans;
int n,m;
mat pre[33],pw[33];
mat operator*(mat X,mat Y) {
    mat Z;
    Z.a=((LL)X.a*Y.a+(LL)X.b*Y.c)%mod;
    Z.b=((LL)X.a*Y.b+(LL)X.b*Y.d)%mod;
    Z.c=((LL)X.c*Y.a+(LL)X.d*Y.c)%mod;
    Z.d=((LL)X.c*Y.b+(LL)X.d*Y.d)%mod;
    return Z;
}
mat operator+(mat X,mat Y) {
    mat Z;
    Z.a=(X.a+Y.a)%mod;
    Z.b=(X.b+Y.b)%mod;
    Z.c=(X.c+Y.c)%mod;
    Z.d=(X.d+Y.d)%mod;
    return Z;
}
mat qpow(mat a,int b) {
    mat w=E;
    while(b){
        if(b&1) w=w*a;
        a=a*a;
        b>>=1;
    }
    return w;
}
mat vsum(int n){
    if(n==0) return ZR;
    if(n==1) return E;
    int m=1,t=0;
    while(m<=n) m<<=1,++t;
    m>>=1,--t;
    return pre[t]+pw[t]*vsum(n-m);
}
void prepare(mat A){//A矩阵是系数矩阵的ai次方 
    for(int i=0;i<=30;++i){
        if(i==0) pw[i]=A;
        else pw[i]=pw[i-1]*pw[i-1];
        if(i==0) pre[i]=E;//单位矩阵 
        else pre[i]=pre[i-1]*(E+pw[i-1]);
    }
}
mat solve(int d) {
    if(d>=m) return ZR;
    int k=(m-1)/d;
    prepare(qpow(F,d));
    return qpow(F,m-1-k*d)*vsum(k);
}
int main() {
  freopen("password.in" , "r", stdin);
  freopen("password.out", "w", stdout);
    scanf("%d%d",&n,&m);
    if(m<=2){
        printf("1\n");
        return 0;
    }
    E.a=E.d=1;
    F.a=F.b=F.c=1;
    Ans=Ans+qpow(F,m-1);//先算出纯 fib序列 

    for(int i=1;i<=n;++i){// 
        int x;
        scanf("%d",&x);
        Ans=Ans+solve(x);
    }
    printf("%d\n",Ans.a);
}

