/**************************************************************
    Problem: 1833
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1312 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long 
using namespace std;
inline ll read()
{
    ll x=0,flag=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')flag=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*flag;
}
struct D{ll cnt[10];D(){memset(cnt,0,sizeof(cnt));}};
ll t[25];
D f[25][10];
D operator+(D x,D y)
{
    D res;
    for(int k=0;k<=9;k++)
        res.cnt[k]=x.cnt[k]+y.cnt[k];
    return res;
}
D calc(ll x)
{
    D res;if(!x){res.cnt[0]=1;return res;}
    int len=15;
    while(t[len]>x)len--;
    for(int i=1;i<len;i++)
        for(int j=1;j<=9;j++)
            res=res+f[i][j];
    res.cnt[0]++;
    int cur=x/t[len];
    for(int i=1;i<cur;i++)
        res=res+f[len][i];
    x%=t[len];
    res.cnt[cur]+=x;
    for(int i=len-1;i;i--)
    {
        cur=x/t[i];
        for(int j=0;j<cur;j++)
            res=res+f[i][j];
        x%=t[i];
        res.cnt[cur]+=x;
    }
    return res;
}
int main()
{
    t[1]=1;
    for(int i=2;i<=15;i++) t[i]=t[i-1]*10;
    for(int i=0;i<=9;i++) f[1][i].cnt[i]=1;
    for(int i=2;i<=12;i++)
        for(int j=0;j<=9;j++)
            for(int k=0;k<=9;k++)
            {
                f[i][j]=f[i][j]+f[i-1][k];
                f[i][j].cnt[j]+=t[i-1];
            }
    ll a=read(),b=read();
    D high=calc(b+1),low=calc(a);
    for(int i=0;i<=9;i++)
    {
        printf("%lld",high.cnt[i]-low.cnt[i]);
        if(i!=9) putchar(' ');
    }
    return 0;
}
