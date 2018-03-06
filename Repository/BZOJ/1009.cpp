/**************************************************************
    Problem: 1009
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:60 ms
    Memory:1288 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
 
const int MAXL=25;
 
int N,M,P;
 
struct Mt{int m[MAXL][MAXL];Mt(){memset(m,0,sizeof(m));}};
Mt operator *(Mt a,Mt b)
{
    int i,j,k;
    Mt res;
    for(i=0;i<M;i++)
        for(j=0;j<M;j++)
            for(k=0;k<M;k++)
                res.m[i][j]=(res.m[i][j]+a.m[i][k]*b.m[k][j])%P;
    return res;
}
 
Mt qpow(Mt a,int n)
{
    int i;
    Mt res;
    for(i=0;i<M;i++) res.m[i][i]=1;
    for(i=1;i<=N;i<<=1,a=a*a)
        if(i&n) res=res*a;
    return res;
}
 
int next[MAXL];
char s[MAXL];
int main()
{
    int i,j;
    scanf("%d%d%d",&N,&M,&P);
    scanf("%s",s+1);
    for(i=2,j=0;i<=M;i++)
    {
        while(j&&s[j+1]!=s[i]) j=next[j];
        if(s[j+1]==s[i]) j++;
        next[i]=j;
    }
    Mt dp;
    for(i=0;i<M;i++)
        for(j=0;j<=9;j++)
        {
            int t=i;
            while(t&&s[t+1]-'0'!=j)
                t=next[t];
            if(s[t+1]-'0'==j) t++;
            if(t!=M) dp.m[t][i]=(dp.m[t][i]+1)%P;
        }
    Mt res=qpow(dp,N);
    int ans=0;
    for(i=0;i<M;i++) ans=(ans+res.m[i][0])%P;
    printf("%d\n",ans);
    return 0;
}
