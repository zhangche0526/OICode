#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
typedef long long ll;
const int inf=0x7ffffff;
int F,n,m,W,cnt;
int head[505],dis[505];
bool flag,mark[505];
struct data{int to,next,v;}e[100001];
void ins(int u,int v,int w)
{e[++cnt].to=v;e[cnt].next=head[u];head[u]=cnt;e[cnt].v=w;}
void insert(int u,int v,int w)
{ins(u,v,w);ins(v,u,w);}
void spfa(int x)
{
     mark[x]=1;
     for(int i=head[x];i;i=e[i].next)
         if(e[i].v+dis[x]<dis[e[i].to])
         {
              if(mark[e[i].to]){flag=1;return;}
              else
              {
                   dis[e[i].to]=e[i].v+dis[x];
                   spfa(e[i].to);
              }
         }
     mark[x]=0;
}
bool check()
{
     for(int i=1;i<=n;i++){dis[i]=inf;mark[i]=0;}
     flag=0;
     for(int i=1;i<=n;i++)
         {dis[i]=0;spfa(i);if(flag)return 1;}
     return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	freopen("17.in","r",stdin);
	freopen("17.out","w",stdout);
        cnt=0;
        memset(head,0,sizeof(head));
        cin>>n>>m>>W;
        int u,v,w;
        for(int i=1;i<=m;i++)
           cin>>u>>v>>w,insert(u,v,w);
        for(int i=1;i<=W;i++)
           cin>>u>>v>>w,ins(u,v,-w);
        if(check()) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    return 0;
}
