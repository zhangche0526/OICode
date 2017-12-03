/**************************************************************
    Problem: 1005
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:80 ms
    Memory:1344 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
 
const int MAXN=1005;
 
int n;
int pIdx[MAXN],pri[MAXN],pcnt,dgr[MAXN];
bool notPri[MAXN];
void initPri(int r)
{
    int i,j;
    for(i=2;i<=r;i++)
    {
        if(!notPri[i]) pri[++pcnt]=i;
        for(j=1;j<=pcnt&&pri[j]*i<=r;j++)
        {
            notPri[pri[j]*i]=true;
            if(i%pri[j]==0) break;
        }
    }
}
  
void addIdx(int x,int idx)
{
    for(int i=1;i<=pcnt&&x>1;i++)
        while(x%pri[i]==0)
            x/=pri[i],pIdx[i]+=idx;
}
 
int dig[MAXN*10],dL;
int main()
{
    int i,j;
    initPri(1000);
    scanf("%d",&n);
    if(n==1)
    {
        scanf("%d",&dgr[1]);
        if(dgr[1]==0||dgr[1]==-1) printf("1\n");
        else printf("0\n");
        return 0;
    }
    if(n==2)
    {
        scanf("%d%d",&dgr[1],&dgr[2]);
        if(dgr[1]==1&&dgr[2]==1) printf("1\n");
        else printf("0\n");
        return 0;
    }
    int dSum=0,limNcnt=0;bool noAns=false;
    for(i=1;i<=n;i++)
    {
        scanf("%d",&dgr[i]);
        if(dgr[i]==0||dgr[i]>=n) noAns=true;
        if(dgr[i]==-1)
            continue;
        limNcnt++;
        dSum+=dgr[i]-1;
        for(j=1;j<=dgr[i]-1;j++)
            addIdx(j,-1);
    }
    for(i=1;i<=n-2;i++) addIdx(i,1);
    if(noAns){printf("0\n");return 0;}
    for(i=1;i<=n-2-dSum;i++) addIdx(i,-1);
    addIdx(n-limNcnt,n-2-dSum);
    dL=dig[1]=1;
    for(i=1;i<=pcnt;i++)
    {
        while(pIdx[i])
        {
            pIdx[i]--;
            for(j=1;j<=dL;j++) dig[j]*=pri[i];
            for(j=1;j<dL;j++) dig[j+1]+=dig[j]/10,dig[j]%=10;
            while(dig[dL]>=10)
            {
                dig[dL+1]+=dig[dL]/10,dig[dL]%=10;
                dL++;
            }
        }
    }
    for(i=dL;i;i--)
        printf("%d",dig[i]);
    printf("\n");
    return 0;
}
