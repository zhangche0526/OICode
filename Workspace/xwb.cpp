#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=1000005;
int cnt=1,n,m;
int a[MAXN];
int ls[MAXN<<2],rs[MAXN<<2];
//左端点，右端点
int lp[MAXN<<2],rp[MAXN<<2];
//最大值和次大值
int fir[MAXN<<2],sec[MAXN<<2];
//最大值数量
int tot[MAXN<<2];
long long sum[MAXN<<2];
//更新父亲节点
void update(int u){
    fir[u]=max(fir[ls[u]],fir[rs[u]]);
    sec[u]=max(sec[ls[u]],sec[rs[u]]);
    if(fir[ls[u]]!=fir[rs[u]])
        sec[u]=max(sec[u],min(fir[ls[u]],fir[rs[u]]));
    sum[u]=sum[ls[u]]+sum[rs[u]];
    tot[u]=0;
    if(fir[u]==fir[ls[u]]) tot[u]+=tot[ls[u]];
    if(fir[u]==fir[rs[u]]) tot[u]+=tot[rs[u]];
}
//打tag
void add_tag(int u,int tag){
    sum[u]-=(long long)tot[u]*(fir[u]-tag);
    fir[u]=tag;
}
//下传tag
void push_down(int u){
    if(fir[u]<fir[ls[u]]) add_tag(ls[u],fir[u]);
    if(fir[u]<fir[rs[u]]) add_tag(rs[u],fir[u]);
}
//建树
void build(int u,int l,int r){
    lp[u]=l,rp[u]=r;
    if(l==r){
        sum[u]=fir[u]=a[l];
        tot[u]=1;
        sec[u]=-1;
        return;
    }
    int mid=l+r>>1;
    ls[u]=++cnt;
    build(ls[u],l,mid);
    rs[u]=++cnt;
    build(rs[u],mid+1,r);
    update(u);
}
//修改
void modify(int u,int l,int r,int x){
    if(fir[u]<=x) return;
    if(l<=lp[u] && rp[u]<=r && sec[u]<x){
        add_tag(u,x);
        return;
    }
    push_down(u);
    int mid=lp[u]+rp[u]>>1;
    if(l<=mid) modify(ls[u],l,r,x);
    if(r>mid) modify(rs[u],l,r,x);
    update(u);
}
//查询区间最大值
int ask_max(int u,int l,int r){
    if(l<=lp[u] && rp[u]<=r) return fir[u];
    push_down(u);
    int mid=lp[u]+rp[u]>>1;
    int ans=0;
    if(l<=mid) ans=max(ans,ask_max(ls[u],l,r));
    if(r>mid) ans=max(ans,ask_max(rs[u],l,r));
    return ans;
}
//查询区间和
long long ask_sum(int u,int l,int r){
    if(l<=lp[u] && rp[u]<=r) return sum[u];
    push_down(u);
    int mid=lp[u]+rp[u]>>1;
    long long ans=0;
    if(l<=mid) ans+=ask_sum(ls[u],l,r);
    if(r>mid) ans+=ask_sum(rs[u],l,r);
    return ans;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i]);
        build(1,1,n);
        for(int i=1;i<=m;++i){
            int opt,x,y;
            scanf("%d%d%d",&opt,&x,&y);
            if(opt==1) printf("%d\n",ask_max(1,x,y));
            else if(opt==2) printf("%I64d\n",ask_sum(1,x,y));
            else{
                int t;
                scanf("%d",&t);
                modify(1,x,y,t);
            }
        }
    }
    return 0;
}
