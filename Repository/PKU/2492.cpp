#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=2017;

int T;
int n,m;
int fa[MAXN];
bool rela[MAXN];

int calAnc(int x)
{
	if(fa[x]==x) return x;
	int xFa=fa[x];
	fa[x]=calAnc(xFa);
	rela[x]^=rela[xFa];
	return fa[x];
}

void join(int x,int y)
{
	int xAnc=calAnc(x),yAnc=calAnc(y);
	if(xAnc==yAnc) return;
	fa[xAnc]=yAnc;
	rela[xAnc]=!(rela[x]^rela[y]);
}

int main()
{
	scanf("%d",&T);
	int i,j;
	for(i=1;i<=T;i++)
	{
		scanf("%d%d",&n,&m);
		memset(rela,false,sizeof(rela));
		for(j=1;j<=n;j++) fa[j]=j;
		bool ok=true;
		for(j=1;j<=m;j++)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			if(calAnc(u)==calAnc(v))
			{
				if(rela[u]==rela[v])
					ok=false;
			}else join(u,v);
		}
		if(!ok)
			printf("Scenario #%d:\nSuspicious bugs found!\n\n",i);
		else printf("Scenario #%d:\nNo suspicious bugs found!\n\n",i);
	}
}
