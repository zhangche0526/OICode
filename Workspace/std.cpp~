#include <cstdio>
#include <algorithm>
#include <climits>
using std::max;
using std::sort;
const int MAXN=10005,MAXQ=105;
int q,grt,sum_sz;
int he[MAXN],de[MAXN],sz[MAXN];
int qry[MAXN],ans[MAXQ];
bool use[MAXN];
struct line{int to,nex,w;}ed[MAXN<<1];
inline void addE(int u,int v,int w){
    static int cnt;
    ed[++cnt]=(line){v,he[u],w};
    he[u]=cnt;
}
void get_grt(int u,int fa){
    static int max_subT_sz[MAXN]={INT_MAX};
    sz[u]=1,max_subT_sz[u]=0;
    for(int i=he[u],v;i;i=ed[i].nex){
        v=ed[i].to;
        if(!use[v] && v!=fa){
            get_grt(v,u);
            sz[u]+=sz[v];
            max_subT_sz[u]=max(max_subT_sz[u],sz[v]);
        }
    }
    max_subT_sz[u]=max(max_subT_sz[u],sum_sz-sz[u]);
    if(max_subT_sz[u]<max_subT_sz[grt]) grt=u;
}
void DFS(int u,int fa,int de){
    ::de[++::de[0]]=de;
    for(int i=he[u],v;i;i=ed[i].nex){
        v=ed[i].to;
        if(!use[v] && v!=fa) DFS(v,u,de+ed[i].w);
    }
}
bool lt(int a,int b){return a<b;}
bool leq(int a,int b){return a<=b;}
inline int solve(int k,bool jud(int,int)){
    int l=1,r=de[0],ret=0;
    if(k==0) return jud(de[1],k);
    while(l<r){
        if(jud(de[l]+de[r],k)) ret+=r-l,++l;
        else --r;
    }
    return ret;
}
void treeDC(int u){
    use[u]=true;
    de[0]=0;
    DFS(u,0,0);
    sort(de+1,de+de[0]+1);
    for(int i=1;i<=q;++i)
        ans[i]+=solve(qry[i],leq)-solve(qry[i],lt);
    for(int i=he[u],v,w;i;i=ed[i].nex){
        v=ed[i].to;
        if(use[v]) continue;
        w=ed[i].w;
        de[0]=0;
        DFS(v,0,ed[i].w);
        sort(de+1,de+de[0]+1);
        for(int j=1;j<=q;++j)
            ans[j]-=solve(qry[j],leq)-solve(qry[j],lt);
        grt=0,sum_sz=sz[v];
        get_grt(v,0);
        treeDC(grt);
    }
}
int main(){
    int n;
    scanf("%d%d",&n,&q);
    for(int i=1,u,v,w;i<n;++i){
        scanf("%d%d%d",&u,&v,&w);
        addE(u,v,w),addE(v,u,w);
    }
    for(int i=1;i<=q;++i)
        scanf("%d",&qry[i]);
    sum_sz=n;
    get_grt(1,0);
    treeDC(grt);
    for(int i=1;i<=q;++i)
    if(qry[i]){
        if(ans[i]) puts("Yes");
        else puts("No");
    }else puts("Yes");
    return 0;
}
