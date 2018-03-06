/**************************************************************
    Problem: 3512
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:2856 ms
    Memory:92720 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<vector>
typedef long long ll;
const int P=1e9+7,MAXNODE=5e6+5,MOD=1e6+3,MAXN=1e5+5,R=2e6;
 
int N,M;
 
int pri[R>>3],pcnt;
int phi[R+5],phiSum[R+5],mu[MAXN],divProd[MAXN];
std::vector<int> divs[MAXN];
inline void preTab()
{
    int i,j;
    phi[1]=phiSum[1]=mu[1]=divProd[1]=1;
    for(i=2;i<=R;i++)
    {
        if(!phi[i])
        {
            phi[i]=i-1,pri[++pcnt]=i;
            if(i<=N) mu[i]=-1,divProd[i]=i;
        }
        for(j=1;j<=pcnt&&i*pri[j]<=R;j++)
        {
            if(i%pri[j])
            {
                phi[i*pri[j]]=phi[i]*(pri[j]-1);
                if(i*pri[j]<=N) mu[i*pri[j]]=-mu[i],divProd[i*pri[j]]=divProd[i]*pri[j];
            }else
            {
                phi[i*pri[j]]=phi[i]*pri[j];
                if(i*pri[j]<=N) mu[i*pri[j]]=0,divProd[i*pri[j]]=divProd[i];
                break;
            }
        }
        phiSum[i]=(phiSum[i-1]+phi[i])%P;
        if(i<=N) divs[i].push_back(1);
        for(j=1;i*j<=N;j++) divs[i*j].push_back(i);
    }
}
 
struct PR
{
    int n,m;
    inline ll hash(){return (ll)n<<30|m;}
    PR(int n=0,int m=0):n(n),m(m){};
};
bool operator ==(const PR &a,const PR &b){return a.n==b.n&&a.m==b.m;}
 
struct HM
{
    PR rsp[MAXNODE];int val[MAXNODE];
    int hd[MOD+5],nxt[MOD+5],sz,nullFlag;
    HM():sz(0),nullFlag(-1){};
    int &find(PR x)
    {
        for(int i=hd[x.hash()%MOD];i;i=nxt[i])
            if(x==rsp[i]) return val[i];
        return nullFlag;
    }
    int &operator[](PR x)
    {
        int &v=find(x);
        if(~v) return v;
        rsp[++sz]=x,nxt[sz]=hd[x.hash()%MOD],hd[x.hash()%MOD]=sz;
        return val[sz];
    }
} hm;
 
int G(int n)
{
    if(n<=R) return phiSum[n];
    PR x(1,n);
    int res=hm.find(x);
    if(~res) return res;
    res=((ll)n*(n+1)>>1)%P;
    int l,r=1;
    while(r<n)
    {
        l=r+1,r=n/(n/l);
        res=(res-(ll)(r-l+1)*G(n/l))%P;
    }
    return hm[x]=(res+P)%P;
}
 
int F(int n,int m)
{
    if(n==1) return G(m);
    if(m==0) return 0;
    if(mu[n]==0) return (ll)F(divProd[n],m)*(n/divProd[n])%P;
    PR x(n,m);
    int res=hm.find(x);
    if(~res) return res; 
    res=0;
    for(int i=0,d;i<divs[n].size();i++)
    {
        d=divs[n][i];
        res=(res+(ll)phi[n/d]*F(d,m/d))%P;
    }
    return hm[x]=res;
}
 
int main()
{   
    scanf("%d%d",&N,&M);
    preTab();
    int i,ans=0;
    for(i=1;i<=N;i++) ans=(ans+F(i,M))%P;
    printf("%d\n",ans);
    return 0;
}
