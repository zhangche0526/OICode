/**************************************************************
    Problem: 3262
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:1016 ms
    Memory:6372 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
 
const int MAXN=1e5+5,MAXK=2e5+5;
 
int N,ncnt,K;
 
struct Tri{int a,b,c;int cnt,lv;} flw[MAXN];
bool operator ==(const Tri &x,const Tri &y)
{return x.a==y.a&&x.b==y.b&&x.c==y.c;}
bool operator !=(const Tri &x,const Tri &y){return !(x==y);}
bool operator <(const Tri &x,const Tri &y)
{return x.a<y.a||(x.a==y.a&&x.b<y.b)||(x.a==y.a&&x.b==y.b&&x.c<y.c);}
 
struct FT
{
    int na[MAXK];
    void add(int x,int v){for(;x<=K;x+=x&(-x)) na[x]+=v;}
    int sum(int x){int res=0;for(;x;x-=x&(-x)) res+=na[x];return res;}
    void clean(int x){for(;x<=K;x+=x&(-x)) if(na[x]) na[x]=0;else break;}
} ft;
 
void cdq(int l,int r)
{
    if(l==r) {flw[l].lv=flw[l].cnt-1;return;}
    int i,mid=(l+r)>>1;
    cdq(l,mid);cdq(mid+1,r);
    static Tri tmp[MAXN];
    int p1=l,p2=mid+1;
    for(i=l;i<=r;i++)
    {
        if(p2>r||(p1<=mid&&flw[p1].b<=flw[p2].b))
        {
            tmp[i]=flw[p1++];
            ft.add(tmp[i].c,tmp[i].cnt);
        }
        else
        {
            tmp[i]=flw[p2++];
            tmp[i].lv+=ft.sum(tmp[i].c);
        }
    }
    for(i=l;i<=r;i++) flw[i]=tmp[i],ft.clean(flw[i].c);
}
 
int main()
{
    int i;
    scanf("%d%d",&N,&K);
    for(i=1;i<=N;i++) scanf("%d%d%d",&flw[i].a,&flw[i].b,&flw[i].c),flw[i].cnt=1;
    std::sort(flw+1,flw+1+N);
    for(i=1;i<=N;i++)
        if(flw[i]!=flw[i-1]) flw[++ncnt]=flw[i];
        else flw[ncnt].cnt++;
    cdq(1,ncnt);
    static int ans[MAXN];
    for(i=1;i<=ncnt;i++) ans[flw[i].lv]+=flw[i].cnt;
    for(i=0;i<=N-1;i++) printf("%d\n",ans[i]);
    return 0;
}
