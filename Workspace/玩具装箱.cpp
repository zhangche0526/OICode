#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=5e4+5;
 
int n,L,C;

ll f[MAXN],g[MAXN];

inline double K(int a,int b)
{return double(f[b]-f[a]+(g[b]+C)*(g[b]+C)-(g[a]+C)*(g[a]+C))/(g[b]-g[a]<<1);}
 
int main()
{
    int i;
    scanf("%d%d",&n,&L);C=L+1;
    for(i=1;i<=n;i++) scanf("%lld",&g[i]);
    for(i=2;i<=n;i++) g[i]+=g[i-1];
    for(i=1;i<=n;i++) g[i]+=i;
    static int dq[MAXN];int hd,tl;
    hd=1,tl=0;dq[++tl]=0;
    for(i=1;i<=n;i++)
    {
        while(hd<tl&&K(dq[hd],dq[hd+1])<=g[i]) hd++;
        int t=dq[hd];
        f[i]=f[t]+(g[i]-g[t]-C)*(g[i]-g[t]-C);
        while(hd<tl&&K(dq[tl],i)<K(dq[tl-1],dq[tl])) tl--;
        dq[++tl]=i;
    }
    printf("%lld\n",f[n]);
    return 0;
}
