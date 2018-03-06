/**************************************************************
    Problem: 1002
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1336 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
 
const int MAXN=105;
 
int n;
 
struct BN
{
    int num[105],len;
    BN(){memset(num,0,sizeof(num));len=-1;}
    void adjust()
    {
        for(int i=0;i<=len;i++)
        if(num[i]>9)
        {
            num[i+1]+=num[i]/10;num[i]%=10;
            len=max(len,i+1);
        }
        for(int i=0;i<=len;i++)
        if(num[i]<0)
        {
            num[i+1]-=1;num[i]+=10;
        }
        while(!num[len]) len--;
    }
    BN operator * (int x)const
    {
        BN res=*this;
        for(int i=0;i<=len;i++)  res.num[i]*=x;
        res.adjust();
        return res;
    }
    BN operator + (int x)const
    {
        BN res=*this;
        for(int i=0;i<=len||x;i++) res.num[i]+=x%10,x/=10,res.len=max(res.len,i);
        res.adjust();
        return res;
    }
    BN operator - (BN x)const
    {
        BN res=*this;
        for(int i=0;i<=x.len;i++) res.num[i]-=x.num[i];
        res.adjust();
        return res;
    }
} f[MAXN];
 
int main()
{
    int i;
    scanf("%d",&n);
    f[1]=BN()+1;f[2]=BN()+5;
    for(i=3;i<=n;i++)
        f[i]=f[i-1]*3-f[i-2]+2;
    for(i=f[n].len;i>=0;i--) putchar(f[n].num[i]+'0');
    printf("\n");
    return 0;
}
