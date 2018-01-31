#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>

const int MAXN=15,MAXS=1030,INF=1061109567,rm[4]={-1,1,0,0},cm[4]={0,0,-1,1};
struct P{int r,c;P(int r=0,int c=0):r(r),c(c){}};

int n,m;
int mp[MAXN][MAXN];P pt[MAXN];int pcnt;

int f[MAXS][MAXN][MAXN];
bool vis[MAXS][MAXN][MAXN],opt[MAXS][MAXN][MAXN],flg[MAXN][MAXN];
P lap[MAXS][MAXN][MAXN];int las[MAXS][MAXN][MAXN],lac[MAXS][MAXN][MAXN];

void dfs(int S,P p)
{
	if(!f[S][p.r][p.c]) return;
	flg[p.r][p.c]=true;
	if(opt[S][p.r][p.c]) dfs(S,lap[S][p.r][p.c]);
	else dfs(las[S][p.r][p.c],p),dfs(lac[S][p.r][p.c],p);
}

struct HN{int v;P p;};
bool operator <(const HN &a,const HN &b){return a.v>b.v;}
std::priority_queue<HN> heap;

void dijkstra(int f[][MAXN],bool vis[][MAXN],bool opt[][MAXN],P lap[][MAXN])
{
	int r,c;
	for(r=1;r<=n;r++) for(c=1;c<=m;c++)
		heap.push((HN){f[r][c],P(r,c)});
	while(!heap.empty())
	{
		r=heap.top().p.r,c=heap.top().p.c;heap.pop();
		if(vis[r][c]) continue;vis[r][c]=true;
		for(int d=0;d<4;d++)
		{
			int nr=r+rm[d],nc=c+cm[d];
			if(nr<1||nr>n||nc<1||nc>m) continue;
			if(f[nr][nc]>f[r][c]+mp[nr][nc])
				f[nr][nc]=f[r][c]+mp[nr][nc],opt[nr][nc]=true,lap[nr][nc]=P(r,c);
			heap.push((HN){f[nr][nc],P(nr,nc)});
		}
	}
}

inline void dp()
{
	int i,r,c;memset(f,0x3f,sizeof f);
	for(i=0;i<pcnt;i++) f[1<<i][pt[i].r][pt[i].c]=0;
	for(int S=1;S<1<<pcnt;S++)
	{
		for(r=1;r<=n;r++) for(c=1;c<=m;c++)
			for(int s=S;s;s=(s-1)&S)
				if(f[S][r][c]>f[s][r][c]+f[s^S][r][c]-mp[r][c])
					f[S][r][c]=f[s][r][c]+f[s^S][r][c]-mp[r][c],las[S][r][c]=s,lac[S][r][c]=s^S;
		dijkstra(f[S],vis[S],opt[S],lap[S]);
	}
}

int main()
{
	int i,r,c;scanf("%d%d",&n,&m);
	for(r=1;r<=n;r++) for(c=1;c<=m;c++)
	{
		scanf("%d",&mp[r][c]);
		if(!mp[r][c]) pt[pcnt++]=P(r,c);
	}
	dp();
	int mnv=INF;P mnp;
	for(i=0;i<pcnt;i++)
		if(mnv>f[(1<<pcnt)-1][pt[i].r][pt[i].c])
			mnv=f[(1<<pcnt)-1][pt[i].r][pt[i].c],mnp=pt[i];
	printf("%d\n",mnv);
	dfs((1<<pcnt)-1,mnp);
	for(r=1;r<=n;r++) for(c=1;c<=m;c++)
	{
		if(!mp[r][c]) putchar('x');
		else if(flg[r][c]) putchar('o');
		else putchar('_');
		if(c==m) putchar('\n');
	}
	return 0;
}
