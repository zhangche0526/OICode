#include<iostream>
#include<cstdio>
typedef long long ll;
 
const int MAXN=1e6+5;
 
bool notPri[MAXN];
int pri[MAXN],pcnt,mu[MAXN];
 
int initmu(int N)
{
    int i,j;
    mu[1]=1;
    for(i=2;i<=N;i++)
    {
        if(!notPri[i])
            pri[++pcnt]=i,mu[i]=-1;
        for(j=1;j<=pcnt&&i*pri[j]<=N;j++)
        {
            notPri[i*pri[j]]=true;
            if(i%pri[j]) mu[i*pri[j]]=-mu[i];
            else {mu[i*pri[j]]=0;break;}
        }
    }
}
 
ll sum[MAXN];
 
int main()
{
    int i,j;
    int n,m,d;scanf("%d%d%d",&n,&m,&d);
    n/=d,m/=d;
    if(n>m) std::swap(n,m);
    initmu(n);
    for(i=1;i<=n;i++)
        sum[i]=mu[i]+sum[i-1];
    ll ans=0;
    for(i=1;i<=n;i=j+1)
    {
        j=std::min(n/(n/i),m/(m/i));
        ans+=(sum[j]-sum[i-1])*(ll)(n/i)*(ll)(m/i);
    }
    printf("%lld\n",ans);
    return 0;
}
