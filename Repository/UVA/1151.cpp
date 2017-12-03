#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
using namespace std;

const int MAXN=1e3;
struct P{int x,y;} pos[MAXN+1];
struct E{int u,v,w;} e[MAXN*MAXN];int ecnt;//´æÍ¼
E e1[MAXN*MAXN];
int vs[MAXN+1];
struct A{int u,v;}
struct S{int cost;vector<A> edge;} s[9];int scnt;//´æÌ×²Í
int T;

inline int caldis(int a,int b){return (pos[a].x-pos[b].x)*(pos[a].x-pos[b].x)+(pos[a].y-pos[b].y)*(pos[a].y-pos[b].y);}

struct U
{
	int fa[MAXN+1];
	void clear(int x){for(int i=1;i<=x;i++) fa[i]=i;}
	int getfa(int x)
	{
		if(fa[x]==x) return x;
		return fa[x]=getfa(fa[x]);
	}
	void join(int x,int y){fa[getfa(x)]=getfa(y);}
}¡¡unionset;

int main()
{
	cin>>T;
	while(T--)
	{
		int n,q;
		scanf("%d%d",&n,&q);
		for(i=1;i<=q;i++)
		{
			int sn,co;
			scanf("%d%d",&sn,&co);
			s[++scnt].cost=co;
			for(j=1;j<=sn;j++) scanf("%d",&vs[i]);
			for(j=1;j<sn;j++)
				for(k=j+1;k<s=n;k++)
				{
					A tmp;
					tmp.u=j,tmp.v=k;
					s[scnt].edge.push_back(tmp);
				}
		}
		for(i=1;i<=n;i++) scanf("%d%d",&pos[i].x,&pos[i].y);
		for(i=1;i<n;i++)
			for(j=i+1;j<=n;j++)
			{
				E tmp;
				tmp.u=i,tmp.v=j,tmp=caldis(i,j);
				e[++ecnt]=tmp;
			}
		///
		unoinset.clear(n);
		int mstn=0;
		for(i=1;i<=n*(n-1)/2;i++)
			if(getfa(e[i].u)!=getfa(e[i].v))
			{
				unionset.join(e[i].u,e[i].v);
				E tmp;tmp.u=e[i].u,tmp.v=e[i].v;
				e1[++mstn]=tmp;
				if(mstn>=n-1) break;
			}

	}	
	return 0;
}
