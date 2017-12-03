/**************************************************************
    Problem: 4719
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:9936 ms
    Memory:52772 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
 
const int MAXN=3e5+5;
 
int N,M;
 
struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v);addEdge(v,u);}
 
struct C{int s,t,lca,len;} chn[MAXN];
 
int w[MAXN],dpt[MAXN];
 
int fa[MAXN];
inline void initUFS(){for(int i=1;i<=N;i++) fa[i]=i;}
int findAnc(int x){return fa[x]==x?x:fa[x]=findAnc(fa[x]);}
 
struct A{int next,to,id;} lcaAsk[MAXN<<1];int acnt,hd[MAXN];
void addAsk(int u,int v,int id){lcaAsk[++acnt]=(A){hd[u],v,id};hd[u]=acnt;}
void addAsk2(int u,int v,int id){addAsk(u,v,id);addAsk(v,u,id);}
 
bool vis[MAXN];
void dfsPre(int u)
{
    int i;
    vis[u]=true;
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;if(vis[v]) continue;
        dpt[v]=dpt[u]+1;dfsPre(v);fa[v]=u;
    }
    for(i=hd[u];i;i=lcaAsk[i].next) if(vis[lcaAsk[i].to])
            chn[lcaAsk[i].id].lca=findAnc(lcaAsk[i].to);
}
 
int chnCnt[MAXN],Cnt[MAXN*3];
std::vector<int> vec1[MAXN],vec2[MAXN];
 
int ans[MAXN];
 
void dfsU(int u,int la)
{
    int i,k=w[u]+dpt[u];int tmp=Cnt[k];
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;if(v==la) continue;
        dfsU(v,u);
    }
    Cnt[dpt[u]]+=chnCnt[u];
    ans[u]=Cnt[k]-tmp;
    for(i=0;i<vec1[u].size();i++) Cnt[vec1[u][i]]--;
}
 
void dfsD(int u,int la)
{
    int i,k=dpt[u]-w[u];int tmp=Cnt[MAXN+k];
    for(i=G[u];i;i=e[i].next)
    {
        int v=e[i].to;if(v==la) continue;
        dfsD(v,u);
    }
    for(i=0;i<vec1[u].size();i++) Cnt[MAXN+vec1[u][i]]++;
    ans[u]+=Cnt[MAXN+k]-tmp;
    for(i=0;i<vec2[u].size();i++) Cnt[MAXN+vec2[u][i]]--;
}
 
int main()
{
    int i;
    scanf("%d%d",&N,&M);
    for(i=1;i<N;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        addEdge2(u,v);
    }
    for(i=1;i<=N;i++) scanf("%d",w+i);
    for(i=1;i<=M;i++)
    {
        scanf("%d%d",&chn[i].s,&chn[i].t);
        addAsk2(chn[i].s,chn[i].t,i);
    }
    initUFS();dpt[1]=1;dfsPre(1);
    for(i=1;i<=M;i++) chn[i].len=dpt[chn[i].s]+dpt[chn[i].t]-2*dpt[chn[i].lca];
     
    for(i=1;i<=M;i++) chnCnt[chn[i].s]++;
    for(i=1;i<=M;i++) vec1[chn[i].lca].push_back(dpt[chn[i].s]);
    dfsU(1,0);
 
    memset(Cnt,0,sizeof(Cnt));
    for(i=1;i<=N;i++) vec1[i].clear();
    for(i=1;i<=M;i++) 
        vec1[chn[i].t].push_back(dpt[chn[i].t]-chn[i].len),
        vec2[chn[i].lca].push_back(dpt[chn[i].t]-chn[i].len);
    dfsD(1,0);
 
    for(i=1;i<=M;i++) 
        if(dpt[chn[i].s]-dpt[chn[i].lca]==w[chn[i].lca])
            ans[chn[i].lca]--;
    for(i=1;i<N;i++) printf("%d ",ans[i]);printf("%d",ans[N]);
    return 0;
}
