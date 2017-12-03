/**************************************************************
    Problem: 3944
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:5532 ms
    Memory:36616 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
const int MAXP=1e6+5,M=2e6,MAXT=1e4+5;//MAXT has nothing to do with T,T=transformed lenth
 
int N;
 
int pri[MAXP],pcnt;
ll phiSum[M+5],muSum[M+5];
inline void preTab()
{
    int i,j;
    phiSum[1]=muSum[1]=1;
    for(i=2;i<=M;i++)
    {
        if(!phiSum[i]) phiSum[i]=i-1,muSum[i]=-1,pri[++pcnt]=i;
        for(j=1;j<=pcnt&&i*pri[j]<=M;j++)
        {
            if(i%pri[j]) phiSum[i*pri[j]]=phiSum[i]*(pri[j]-1),muSum[i*pri[j]]=-muSum[i];
            else {phiSum[i*pri[j]]=phiSum[i]*pri[j],muSum[i*pri[j]]=0;break;}
        }
    }
    for(i=1;i<M;i++) phiSum[i+1]+=phiSum[i],muSum[i+1]+=muSum[i];
}
 
ll phiSumT[MAXT],muSumT[MAXT];bool vis[MAXT];
inline ll getPhiSum(int x){return x<=M?phiSum[x]:phiSumT[N/x];}
inline ll getMuSum(int x){return x<=M?muSum[x]:muSumT[N/x];}
 
void solve(int x)
{
    if(x<=M) return;int posT=N/x;
    if(vis[posT]) return;vis[posT]=true;
    phiSumT[posT]=((ll)x+1)*x>>1,muSumT[posT]=1;
    int l,r=1;
    while(r<x)
    {
        l=r+1,r=x/(x/l);solve(x/l);
        phiSumT[posT]-=getPhiSum(x/l)*(r-l+1),
        muSumT[posT]-=getMuSum(x/l)*(r-l+1);
    }
}
 
int main()
{
    preTab();
    int T;scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);memset(vis,false,sizeof(vis));
        if(N<=M) printf("%lld %lld\n",phiSum[N],muSum[N]);
        else solve(N),printf("%lld %lld\n",phiSumT[1],muSumT[1]);
    }
    return 0;
}
