#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=2e4;
int fa[MAXN+1];
int getfa(int x)
{
	if(fa[x]==x) return x;
	int root=getfa(fa[x]);
	d[x]+=d[fa[x]];
	return fa[x]=root;
}
int d[MAXN+1];
int T;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int N,u,v;
		char cmd[9];
		scanf("%d",&N);
		for(int i=1;i<=N;i++) fa[i]=i;
		memset(d,0,sizeof(d));
		while(scanf("%s",cmd)&&cmd[0]!='O')
		{
			if(cmd[0]=='E')
			{
				scanf("%d",&u);
				getfa(u);
				prinf("%d\n",d[u]);
			}
		}
	}
	return 0;
}
