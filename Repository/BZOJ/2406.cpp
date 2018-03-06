/**************************************************************
    Problem: 2406
    User: zhangche0526
    Language: C++
    Result: Accepted
    Time:304 ms
    Memory:2428 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using std::abs;
using std::min;
inline void umn(int &a,int b){a=min(a,b);}
using std::max;
inline void umx(int &a,int b){a=max(a,b);}
 
const int MAXV=505,MAXE=4e4+1e3,INF=1061109567;
 
int s,t,S,T;
 
struct E{int next,to,cap;} e[MAXE<<1];int ecnt,G[MAXV];
void addEdge(int u,int v,int c)
{
    e[++ecnt]=(E){G[u],v,c};G[u]=ecnt;
    e[++ecnt]=(E){G[v],u,0};G[v]=ecnt;
//  printf("(%d->%d,%d)\n",u,v,c);
}
 
std::queue<int> que;
int dpt[MAXV];
bool calDpt()
{
    memset(dpt,-1,sizeof dpt);
    dpt[S]=0;que.push(S);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        for(int i=G[u];i;i=e[i].next) if(e[i].cap>0)
        {
            int v=e[i].to;
            if(~dpt[v]) continue;
            dpt[v]=dpt[u]+1;
            que.push(v);
        }
    }
    return ~dpt[T];
}
 
int iter[MAXV];
int calF(int u,int f)
{
    if(u==T) return f;
    for(int &i=iter[u];i;i=e[i].next) if(e[i].cap>0)
    {
        int v=e[i].to;
        if(dpt[v]!=dpt[u]+1) continue;
        int res=calF(v,min(f,e[i].cap));
        if(res>0)
        {
            e[i].cap-=res,e[i^1].cap+=res;
            return res;
        }
    }
    return 0;
}
 
int maxFlow()
{
    int res=0,f;
    while(calDpt())
    {
        memcpy(iter,G,sizeof G);
        while(f=calF(S,INF)) res+=f;
    }
    return res;
}
 
const int MAXN=205;
 
int n,m,L,R;
int A[MAXN][MAXN],rs[MAXN],cs[MAXN];
 
int ndF[MAXN<<1];
void buildGraph(int ans)
{
    int i,j;
    memset(ndF,0,sizeof ndF);
    memset(G,0,sizeof G);ecnt=1;
    s=n+m+1,t=s+1;
    for(i=1;i<=n;i++) for(j=1;j<=m;j++) addEdge(i,n+j,R-L),ndF[i]-=L,ndF[n+j]+=L;
    for(i=1;i<=n;i++) addEdge(s,i,2*ans),ndF[s]-=rs[i]-ans,ndF[i]+=rs[i]-ans;
    for(j=1;j<=m;j++) addEdge(n+j,t,2*ans),ndF[n+j]-=cs[j]-ans,ndF[t]+=cs[j]-ans;
    addEdge(t,s,INF);
    S=t+1,T=S+1;
    for(i=1;i<=t;i++)
    {
        if(ndF[i]>0) addEdge(S,i,ndF[i]);
        else if(ndF[i]<0) addEdge(i,T,-ndF[i]);
    }
}
 
inline bool jud(int ans)
{
    buildGraph(ans);
    maxFlow();
    for(int i=G[S];i;i=e[i].next)
        if(e[i].cap>0) return false;
    return true;
}
 
inline int preprc()
{
    int i,j;
    int res=0;
    int v=L+R>>1;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++) rs[i]+=A[i][j];
        umx(res,abs(rs[i]-m*v));
    }
    for(j=1;j<=m;j++)
    {
        for(i=1;i<=n;i++) cs[j]+=A[i][j];
        umx(res,abs(cs[j]-n*v));
    }
    return res;
}
 
int main()
{
    int i,j;scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) for(j=1;j<=m;j++)
        scanf("%d",&A[i][j]);
    scanf("%d%d",&L,&R);
    int l=0,r=preprc();
    while(l<=r)
    {
        int mid=l+r>>1;
        if(jud(mid)) r=mid-1;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;
}
 
/*
3 4
1 3 5 4
2 1 4 1
7 2 6 2
2 5
*/
?
