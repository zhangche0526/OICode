/**************************************************************
    Problem: 1010
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:176 ms
    Memory:2464 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=5e4+5;
 
ll n,L,C;
ll f[MAXN],g[MAXN],que[MAXN];
 
inline double calSlop(int j,int k)
{return (f[k]-f[j]+(g[k]+C)*(g[k]+C)-(g[j]+C)*(g[j]+C))/(2.0*(g[k]-g[j]));}
 
int main()
{
    int i;
    scanf("%lld%lld",&n,&L);C=L+1;
    for(i=1;i<=n;i++) scanf("%lld",&g[i]);
    for(i=2;i<=n;i++) g[i]+=g[i-1];
    for(i=1;i<=n;i++) g[i]+=i;
    int hd,tl;
    hd=1,tl=0;que[++tl]=0;
    for(i=1;i<=n;i++)
    {
        while(hd<tl&&calSlop(que[hd],que[hd+1])<=g[i]) hd++;
        int t=que[hd];
        f[i]=f[t]+(g[i]-g[t]-C)*(g[i]-g[t]-C);
        while(hd<tl&&calSlop(que[tl],i)<calSlop(que[tl-1],que[tl])) tl--;
        que[++tl]=i;
    }
    printf("%lld\n",f[n]);
    return 0;
}
