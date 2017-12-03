#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=50005;

int fa[MAXN],dis[MAXN];
int calAnc(int x)
{
	int xFa=fa[x];
	if(xFa==x) return x;
	fa[x]=calAnc(xFa);
	dis[x]=(dis[x]+dis[xFa])%300;
	return fa[x];
}
void join(int x,int y,int v)
{
	int xAnc=calAnc(x),yAnc=calAnc(y);
	if(xAnc==yAnc) return;
	fa[xAnc]=yAnc;
	dis[xAnc]=(dis[y]-dis[x]+v+300)%300;
}

int main()
{
	int i,N,M;
	while(scanf("%d%d",&N,&M)!=EOF)
	{
		memset(dis,0,sizeof(dis));
		for(i=1;i<=N;i++) fa[i]=i;
		int ans=0;
		for(i=1;i<=M;i++)
		{
			int x,y,v;scanf("%d%d%d",&x,&y,&v);
			if(calAnc(x)==calAnc(y))
			{
				if((dis[x]+v)%300!=dis[y])
					++ans;
			}else join(x,y,v);
		}
		printf("%d\n",ans);
	}
}
