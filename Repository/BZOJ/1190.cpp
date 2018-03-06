/**************************************************************
    Problem: 1190
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:5144 ms
    Memory:1412 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
 
const int MAXB=32,MAXV=1e3+5;
int n,W;
int f[MAXB][MAXV];
inline void solve()
{
    memset(f,0,sizeof(f));
    int i,j,k,ans=0;
    for(i=1;i<=n;i++)
    {
        int a,b,v;
        scanf("%d%d",&b,&v);
        a=0;
        while(!(b&1)) a++,b>>=1;
        for(j=min(1000,W>>a);j>=b;j--)
        {
            umx(f[a][j],f[a][j-b]+v);
            umx(ans,f[a][j]);
        }
    }
    for(i=1;i<MAXB&&(1<<i)<W;i++)
        for(j=min(1000,W>>i);~j;j--)
        {
            for(k=j;~k;k--)
                umx(f[i][j],f[i][k] + f[i-1][min( ((j-k)<<1)+((W>>(i-1))&1), 1000)]);
            umx(ans,f[i][j]);
        }
    printf("%d\n",ans);
}
int main()
{
    while(scanf("%d%d",&n,&W)&&~n)
        solve();
    return 0;
}
