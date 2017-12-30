#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define id(x,y) (((x)<<2)|(y))
typedef unsigned uint;

const int MAXN=500;int BNUM;

int n,m;

struct BS
{
	uint bs[66];
	void set(){memset(bs,0xff,sizeof bs);}
	void flip(int p){bs[p>>5]^=1U<<p;}
	bool test(int p){return bs[p>>5]&(1U<<p);}
	uint &operator [](int p){return bs[p];}
};
BS G[MAXN],unv;
int typ[MAXN][MAXN];
int dis[MAXN<<2];

std::queue<int> que;
inline void ext(int u,int d){if(~dis[u]) return;dis[u]=d;que.push(u);unv.flip(u);}
void bfs(int v0)
{
	int i;
	memset(dis,-1,sizeof dis);
	unv.set();
	ext(id(v0,0),0);
	while(!que.empty())
	{
		int u=que.front()>>2,ty=que.front()&3,d=dis[que.front()];que.pop();
		if(ty) {ext(id(u,ty-1),d+1);continue;}
		for(i=0;i<=BNUM;i++)
			for(uint vS=G[u][i]&unv[i];vS;vS-=vS&-vS)
				ext(i<<5|__builtin_ctz(vS),d+1);
	}
}

inline void mdf(int u,int v,int w)
{
	if(~typ[u][v]) G[u].flip(id(v,typ[u][v]));
	typ[u][v]=w;
	if(~typ[u][v]) G[u].flip(id(v,typ[u][v]));
}

inline int qry(int x)
{
	bfs(x);
	int i,res=0;
	for(i=0;i<n;i++) if(~dis[id(i,0)]) res+=dis[id(i,0)]*(i+1);
	return res;
}

int main()
{
	int i;
	scanf("%d%d",&n,&m);BNUM=id(n-1,3)>>5;
	for(int u=0;u<n;u++) for(int v=0;v<n;v++)
	{
		int w;scanf("%d",&w);w--;
		typ[u][v]=w;
		if(~w) G[u].flip(id(v,w));
	}
	for(i=1;i<=m;i++)
	{
		char opt[10];scanf("%s",opt);
		if(opt[0]=='C')
		{
			int u,v,w;scanf("%d%d%d",&u,&v,&w);u--,v--,w--;
			mdf(u,v,w);
		}else
		{
			int x;scanf("%d",&x);x--;
			printf("%d\n",qry(x));
		}
	}
}
