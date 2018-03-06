/**************************************************************
    Problem: 5130
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1352 ms
    Memory:1288 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
typedef long long ll;
const int MAXN=20,P=998244353;
 
int n,m,ans;
 
int Am[MAXN];
inline void initAm()
{
    Am[0]=1;
    for(int i=1;i<=n&&i<=m;i++)
        Am[i]=(ll)Am[i-1]*(m-i+1)%P;
}
 
int nxt[MAXN],s[MAXN];
 
void dfs(int lv,int v)
{
    if(lv==n)
    {
        int i,j,res=1;
        for(i=1,j;i<n;i++)
        {
            j=nxt[i];
            while(j&&s[i]!=s[j]) j=nxt[j];
            nxt[i+1]=(s[i]==s[j]?j+1:0);
        }
        for(i=1;i<=n;i++) res=(ll)res*(i-nxt[i])%P;
        ans=(ans+(ll)res*Am[v]%P)%P;
        return;
    }
    for(int i=1;i<=v+1;i++) s[lv]=i,dfs(lv+1,i>v?i:v);
}
 
int main()
{
    scanf("%d%d",&n,&m);
    initAm();
    ans=0;
    dfs(0,0);
    printf("%d",ans);
    return 0;
}
?
