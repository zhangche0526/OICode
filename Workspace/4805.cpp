#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long ll;
const int MAXP=1e6+5,M=2e6,MAXT=1e4+5;//MAXT has nothing to do with T,T=transformed lenth
 
int N;
 
int pri[MAXP],pcnt;
ll phiSum[M+5];
inline void preTab()
{
    int i,j;
    phiSum[1]=1;
    for(i=2;i<=M;i++)
    {
        if(!phiSum[i]) phiSum[i]=i-1,pri[++pcnt]=i;
        for(j=1;j<=pcnt&&i*pri[j]<=M;j++)
        {
            if(i%pri[j]) phiSum[i*pri[j]]=phiSum[i]*(pri[j]-1);
            else {phiSum[i*pri[j]]=phiSum[i]*pri[j];break;}
        }
    }
    for(i=1;i<M;i++) phiSum[i+1]+=phiSum[i];
}
 
ll phiSumT[MAXT];bool vis[MAXT];
inline ll getPhiSum(int x){return x<=M?phiSum[x]:phiSumT[N/x];}
void solve(int x)
{
    if(x<=M) return;int posT=N/x;
    if(vis[posT]) return;vis[posT]=true;
    phiSumT[posT]=((ll)x+1)*x>>1;
    int l,r=1;
    while(r<x)
    {
        l=r+1,r=x/(x/l);solve(x/l);
        phiSumT[posT]-=getPhiSum(x/l)*(r-l+1);
    }
}
 
int main()
{
    preTab();
    scanf("%d",&N);
    if(N<=M) printf("%lld\n",phiSum[N]);
    else solve(N),printf("%lld\n",phiSumT[1]);
    return 0;
}
