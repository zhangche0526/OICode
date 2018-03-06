/**************************************************************
    Problem: 4758
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:240 ms
    Memory:45968 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
using std::min;
using std::max;
const int MAXN=55;
 
int n;
 
int na[MAXN];
bool vis[MAXN][MAXN][MAXN][MAXN];
int f[MAXN][MAXN][MAXN][MAXN];
 
int dp(int l,int r,int d,int u)
{
    if(vis[l][r][d][u]) return f[l][r][d][u];
    if(d>u) return -100;
    if(l>r) return 0;
    vis[l][r][d][u]=true;
    if(l==r) return na[l]>=d&&na[r]<=u;
 
    int res=0;
    res=max(res,dp(l+1,r-1,d,u));
    if(na[r]>=d) res=max(res,dp(l+1,r-1,na[r],u)+1);
    if(na[l]<=u) res=max(res,dp(l+1,r-1,d,na[l])+1);
    if(na[r]>=d&&na[l]<=u) res=max(res,dp(l+1,r-1,na[r],na[l])+2);
     
    res=max(res,dp(l+1,r,d,u));
    if(na[l]>=d) res=max(res,dp(l+1,r,na[l],u)+1);
    res=max(res,dp(l,r-1,d,u));
    if(na[r]<=u) res=max(res,dp(l,r-1,d,na[r])+1);
 
    return f[l][r][d][u]=res;
}
 
int main()
{
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;i++) scanf("%d",na+i);
    printf("%d\n",dp(1,n,1,50));
    return 0;
}
