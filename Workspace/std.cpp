#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long ll;

const int P=1e9+7;
const int Inv=(P+1)>>1;

inline ll Pow(ll a,int b){
  ll ret=1; for (;b;b>>=1,a=a*a%P) if (b&1) ret=ret*a%P; return ret;
}

inline void FWT(int *a,int n){
  for (int i=1;i<n;i<<=1)
    for (int j=0;j<n;j+=(i<<1))
      for (int k=0;k<i;k++){
    int x=a[j+k],y=a[j+k+i];
    a[j+k]=(x+y)%P,a[j+k+i]=(x+P-y)%P;
      }
}
inline void UFWT(int *a,int n){
  for (int i=1;i<n;i<<=1)
    for (int j=0;j<n;j+=(i<<1))
      for (int k=0;k<i;k++){
    int x=a[j+k],y=a[j+k+i];
    a[j+k]=(ll)(x+y)*Inv%P,a[j+k+i]=(ll)(x+P-y)*Inv%P;
      }
}

const int maxn=50000;
int vst[maxn+5];
int prime[maxn+5],num;

inline void Pre(){
  for (int i=2;i<=maxn;i++){
    if (!vst[i]) prime[++num]=i;
    for (int j=1;j<=num && (ll)prime[j]*i<=maxn;j++){
      vst[i*prime[j]]=1;
      if (i%prime[j]==0) break;
    }
  }
}

int n,m,_n;
int a[200005];

int main(){
  Pre();
  while (~scanf("%d%d",&_n,&m)){
    n=1;
    while (n<=m) n<<=1;
    for (int i=0;i<n;i++) a[i]=0;
    for (int i=1;i<=num && prime[i]<=m;i++) a[prime[i]]=1;
    FWT(a,n);
    for (int i=0;i<n;i++) a[i]=Pow(a[i],_n);
    UFWT(a,n);
    printf("%d\n",a[0]);
  }
  return 0;
}
