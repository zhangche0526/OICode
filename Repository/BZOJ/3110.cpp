/**************************************************************
    Problem: 3110
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:11160 ms
    Memory:6812 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long ll;
const int MAXN=5e4+5,MAXM=5e4+5;
 
const int rt=1;
struct SEGTN{int l,r,lc,rc;ll sum,tag;} t[MAXN<<1];int tcnt=rt;
void upd(int o){t[o].sum=t[t[o].lc].sum+t[t[o].rc].sum;}
void pushdown(int o)
{
    int lc=t[o].lc,rc=t[o].rc;
    if(t[o].tag) 
    {
        t[lc].tag+=t[o].tag;t[lc].sum+=(t[lc].r-t[lc].l+1)*t[o].tag;
        t[rc].tag+=t[o].tag;t[rc].sum+=(t[rc].r-t[rc].l+1)*t[o].tag;
        t[o].tag=0;
    }   
}
void buildTree(int o,int l,int r)
{
    t[o].l=l,t[o].r=r;
    if(l==r) return;
    int mid=(l+r)>>1;
    t[o].lc=++tcnt;buildTree(t[o].lc,l,mid);
    t[o].rc=++tcnt;buildTree(t[o].rc,mid+1,r);
}
void chDet(int o,int l,int r,ll v)
{
    if(l<=t[o].l&&t[o].r<=r) 
    {
        t[o].tag+=v,t[o].sum+=(t[o].r-t[o].l+1)*v;
        return;
    }
    pushdown(o);
    int mid=(t[o].l+t[o].r)>>1;
    if(l<=mid) chDet(t[o].lc,l,r,v);
    if(r>mid) chDet(t[o].rc,l,r,v);
    upd(o);
}
ll calSum(int o,int l,int r)
{
    if(l<=t[o].l&&t[o].r<=r) return t[o].sum;
    int mid=(t[o].l+t[o].r)>>1;
    pushdown(o);
    ll res=0;
    if(l<=mid) res+=calSum(t[o].lc,l,r);
    if(r>mid) res+=calSum(t[o].rc,l,r);
    return res;
}
 
struct O{int t,l,r,v,id;} opt[MAXM],tmp[MAXM];
int n,m;
ll ans[MAXM];
bool isQ[MAXN];
void dc(int L,int R,int l,int r)
{
    int i,j,mid=(l+r)>>1,newL=L,newR=R;
    if(l==r)
    {
        for(i=L;i<=R;i++) if(opt[i].t==2) ans[opt[i].id]=l;
        return;
    }
    for(i=L;i<=R;i++)
    {
        if(opt[i].t==1)
        {
            if(opt[i].v<=mid) tmp[newL++]=opt[i];
            else
            {
                chDet(rt,opt[i].l,opt[i].r,1);
                tmp[newR--]=opt[i];
            }
        }else
        {
            ll cnt=calSum(rt,opt[i].l,opt[i].r);
            if(opt[i].v>cnt) opt[i].v-=cnt,tmp[newL++]=opt[i];
            else tmp[newR--]=opt[i];
        }
    }
    std::reverse(tmp+newR+1,tmp+R+1);
    for(i=L;i<=R;i++) opt[i]=tmp[i];
    for(i=L;i<=R;i++) if(opt[i].t==1&&opt[i].v>mid) chDet(rt,opt[i].l,opt[i].r,-1);
    dc(L,newL-1,l,mid),dc(newR+1,R,mid+1,r);
}
 
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&opt[i].t,&opt[i].l,&opt[i].r,&opt[i].v);
        if(opt[i].t==2) isQ[i]=true;opt[i].id=i;
    }
    buildTree(rt,0,n);
    dc(1,m,-n,n);
    for(i=1;i<=m;i++) if(isQ[i]) printf("%d\n",ans[i]);
    return 0;
}

