/**************************************************************
    Problem: 3529
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:3664 ms
    Memory:6080 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define D 2147483647
const int N=100000;
bool flag[N+10];
struct F{int d,No;}f[N+10];
struct S{int n,m,a,No,ans;}q[N+10];
int T,prime[N+10],u[N+10],tr[N+10],g[N+10],sum[N+10];
inline bool cmp_1(S x,S y){return x.a<y.a;}
inline bool cmp_2(S x,S y){return x.No<y.No;}
inline bool cmp_3(F x,F y){return x.d<y.d;}
inline int in(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}
inline int quickpow(int x,int y){
    int ans=1;
    while(y){
        if(y&1) ans=ans*x;
        y>>=1; x=x*x;
    }
    return ans;
}
inline void prepare(){
    int i,j;
    f[1].d=f[1].No=u[1]=1;
    for(i=2;i<=N;++i){
        f[i].No=i;
        if(!flag[i]){
            prime[++prime[0]]=i;
            u[i]=-1;
            f[i].d=i+1;
            g[i]=1;
            sum[i]=1+i;
        }
        for(j=1;j<=prime[0]&&i*prime[j]<=N;++j){
            flag[i*prime[j]]=true;
            if(i%prime[j]==0){
                u[i*prime[j]]=0;
                g[i*prime[j]]=g[i]+1;
                sum[i*prime[j]]=sum[i]+quickpow(prime[j],g[i]+1);
                f[i*prime[j]].d=f[i].d/sum[i]*sum[i*prime[j]];
                break;
            }
            u[i*prime[j]]=-u[i];
            f[i*prime[j]].d=f[i].d*f[prime[j]].d;
            g[i*prime[j]]=1;
            sum[i*prime[j]]=prime[j]+1;
        }
    }
}
inline void insert(int x,int y){
    for(;x<=N;x+=x&(-x)) tr[x]+=y;
}
inline int query(int x){
    int sum=0;
    for(;x;x-=x&(-x)) sum+=tr[x];
    return sum;
}
int main(){
    prepare();
    int i,j,now=1,pos;
    T=in();
    for(i=1;i<=T;++i){
        q[i].n=in();q[i].m=in();q[i].a=in();
        q[i].No=i;
    }
    sort(q+1,q+T+1,cmp_1);
    sort(f+1,f+N+1,cmp_3);
    for(i=1;i<=T;++i){
        while(f[now].d<=q[i].a&&now<=N){
            for(j=1;j*f[now].No<=N;++j) 
              insert(j*f[now].No,f[now].d*u[j]);
            ++now;
        }
        if(q[i].n>q[i].m) swap(q[i].n,q[i].m);
        for(j=1;j<=q[i].n;j=pos+1){
            pos=min(q[i].n/(q[i].n/j),q[i].m/(q[i].m/j));
            q[i].ans+=(q[i].n/j)*(q[i].m/j)*(query(pos)-query(j-1));
            q[i].ans&=D;
        }
    }
    sort(q+1,q+T+1,cmp_2);
    for(i=1;i<=T;++i) printf("%d\n",q[i].ans);
}
