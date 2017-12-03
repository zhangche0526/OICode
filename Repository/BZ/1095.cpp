#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<queue>

const int MAXN=1e5+5;

int N,Q;
int fa[MAXN];
bool isOff[MAXN];int offNum;

struct E{int next,to;} e[MAXN<<1];int ecnt,G[MAXN];
void addEdge(int u,int v){e[++ecnt]=(E){G[u],v};G[u]=ecnt;}
void addEdge2(int u,int v){addEdge(u,v),addEdge(v,u);}

class HEAP
{
	private:
		std::priority_queue<int> extH,delH;
		void clean()
		{
			while(!delH.empty()&&extH.top()==delH.top())
			{
				extH.pop();
				delH.pop();
			}
		}
	public:
		void push(int x){extH.push(x);}
		void del(int x){delH.push(x);}
		void pop(){clean();extH.pop();}
		int top(){clean();return extH.top();}
		int scd()
		{
			int t1=top();pop();
			int t2=top();push(t1);
			return t2;
		}
		int size(){return extH.size()-delH.size();}
} A,B[MAXN],C[MAXN];

class LCA
{
	int anc[MAXN][20],dpt[MAXN];
	void dfs(int u,int la)
	{
		for(int i=G[u];i;i=e[i].next)
		{
			int v=e[i].to;
			if(v==la) continue;
			dpt[v]=dpt[u]+1;
			anc[v][0]=u;
			dfs(v,u);        
		}
	}
	public:
	void init()
	{
		dfs(1,0);
		for(int i=1;(1<<i)<=N;i++)
			for(int j=1;j<=N;j++)
				anc[j][i]=anc[anc[j][i-1]][i-1];
	}

	int calLCA(int x, int y)
	{
		int i;
		if(dpt[x]<dpt[y]) std::swap(x,y);
		int maxlogn=std::floor(std::log(N)/std::log(2));
		for(i=maxlogn;i>=0;i--)
			if(dpt[x]-(1<<i)>=dpt[y])
				x=anc[x][i];
		if(x==y) return x;
		for(i=maxlogn;i>=0;i--)
		{
			if(anc[x][i]!=anc[y][i])
			{
				x=anc[x][i];
				y=anc[y][i];
			}
		}
		return anc[x][0];
	}
	int calDis(int x,int y)
	{return dpt[x]+dpt[y]-2*dpt[calLCA(x,y)];}
} lca;

class PDC
{
	private:
		int vis[MAXN],rt;
		int mx[MAXN],sz[MAXN],min;
		void calSz(int u,int la)
		{
			sz[u]=1;mx[u]=0;
			for(int i=G[u];i;i=e[i].next)
			{
				int v=e[i].to;
				if(v!=la&&!vis[v])
				{
					calSz(v,u);
					sz[u]+=sz[v];
					mx[u]=std::max(mx[u],sz[v]);
				}
			}
		}
		void calRt(int r,int u,int la)
		{
			mx[u]=std::max(mx[u],sz[r]-sz[u]);
			if(mx[u]<min) min=mx[u],rt=u;
			for(int i=G[u];i;i=e[i].next)
			{
				int v=e[i].to;
				if(v!=la&&!vis[v])calRt(r,v,u);
			}
		}
		void addC(int u,int la)
		{
			C[rt].push(lca.calDis(u,fa[rt]));
			for(int i=G[u];i;i=e[i].next)
			{      
				int v=e[i].to;                                            
				if(v!=la&&!vis[v])
					addC(v,u);
			}
		}
	public:
		void build(int u,int laRt)
		{
			min=N;
			calSz(u,0);
			calRt(u,u,0);
			vis[rt]=true;fa[rt]=laRt;
			if(laRt) addC(rt,0);
			if(C[rt].size()) B[laRt].push(C[rt].top());
			int oRt=rt;
			for(int i=G[rt];i;i=e[i].next)
			{
				int v=e[i].to;
				if(!vis[v]) build(v,oRt); 
			}
		}
} ptDC;

void turnOn(int x)
{
	for(int i=x;fa[i];i=fa[i])
	{
		if(B[fa[i]].size()>=2) A.del(B[fa[i]].top()+B[fa[i]].scd());
		if(C[i].size()) B[fa[i]].del(C[i].top());
		C[i].del(lca.calDis(fa[i],x));
		if(C[i].size()) B[fa[i]].push(C[i].top());
		if(B[fa[i]].size()>=2) A.push(B[fa[i]].top()+B[fa[i]].scd());
	}
}
void turnOff(int x)
{
	for(int i=x;fa[i];i=fa[i])
	{
		if(B[fa[i]].size()>=2) A.del(B[fa[i]].top()+B[fa[i]].scd());
		if(C[i].size()) B[fa[i]].del(C[i].top());
		C[i].push(lca.calDis(fa[i],x));
		if(C[i].size()) B[fa[i]].push(C[i].top());
		if(B[fa[i]].size()>=2) A.push(B[fa[i]].top()+B[fa[i]].scd());
	}
}

inline int read()
{                                   
	int x=0,flag=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*flag;
}

int main()
{
	int i;
	offNum=N=read();
	for(i=1;i<=N;i++) isOff[i]=true;
	for(i=1;i<N;i++)
	{
		int u,v;u=read();v=read();
		addEdge2(u,v);
	}
	lca.init();
	ptDC.build(1,0);
	for(i=1;i<=N;i++)
		if(B[i].size()>=2)
			A.push(B[i].top()+B[i].scd());
	Q=read();
	char opt[10];
	while(Q--)
	{
		scanf("%s",opt);
		if(opt[0]=='G')
		{
			if(offNum==0) printf("-1\n");
			else if(offNum==1) printf("-1\n");
			else printf("%d\n",A.top());
		}
		else
		{
			int x=read();
			if(isOff[x])
			{
				isOff[x]=false;
				offNum--;
				turnOn(x);
			}else
			{
				isOff[x]=true;
				offNum++;
				turnOff(x);
			}
		}
	}
	return 0;
}
