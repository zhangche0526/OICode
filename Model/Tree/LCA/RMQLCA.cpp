#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>

const int MAXN=5e5+5;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v),addEdge(v,u);}

class LCA
{
    private:
        int ncnt;
        int seq[MAXN<<1],pos[MAXN<<1],dpt[MAXN<<1];
        void dfs(int u,int fa,int d)
        {
            pos[u]=++ncnt,seq[ncnt]=u,dpt[ncnt]=d;
            for(int i=G[u];i;i=e[i].next)
            {
                int v=e[i].to;
                if(v==fa) continue;
                dfs(v,u,d+1);
                seq[++ncnt]=u,dpt[ncnt]=d;
            }
        }
        int f[MAXN<<1][20];
        void initST(int * na,int len)
        {
            int i,k;
            for(i=1;i<=len;i++) f[i][0]=i;
            for(k=1;(1<<k)<=len;k++)
                for(i=1;i+(1<<k)-1<=len;i++)
                {
                    if(dpt[f[i][k-1]]<dpt[f[i+(1<<(k-1))][k-1]])
                        f[i][k]=f[i][k-1];
                    else f[i][k]=f[i+(1<<(k-1))][k-1];
                }
        }
        int calRMQPos(int l,int r)
        {
            int k=std::log(r-l+1)/std::log(2);
            return dpt[f[l][k]]<dpt[f[r+1-(1<<k)][k]]?f[l][k]:f[r+1-(1<<k)][k];
        }
    public:
        void init(int rt)
        {
            ncnt=0;
            memset(seq,0,sizeof(seq));memset(pos,0,sizeof(pos));
            memset(dpt,0,sizeof(dpt));
            dfs(rt,0,1);
            initST(dpt,ncnt);
        }
        int calc(int x,int y)
        {
            x=pos[x],y=pos[y];
            if(x>y) std::swap(x,y);
            return seq[calRMQPos(x,y)];
        }
} lca;

inline int read()
{
    int x=0,flag=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')flag=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*flag;
}

int main()
{
    int N=read(),M=read(),S=read();
    for(int i=1;i<N;i++)
        addEdge2(read(),read());
    lca.init(S);
    while(M--) printf("%d\n",lca.calc(read(),read()));
    return 0;
}
