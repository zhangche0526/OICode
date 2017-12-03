#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=1e5;
int fa[MAXN+1];
int getfa(int x){return fa[x]==x?x:fa[x]=getfa(fa[x]);}

int main()
{
	//freopen("3644.in","r",stdin);
	//freopen("3644.out","w",stdout);
	int x,y;
	while(scanf("%d",&x)&&x!=EOF)
	{
		int ans=0;
		for(int i=1;i<=MAXN;i++) fa[i]=i;
		while(x!=-1)
		{
			scanf("%d",&y);
			int p=getfa(x),q=getfa(y);
			if(p==q) ans++;
			else fa[p]=q;
			scanf("%d",&x);
		}
		printf("%d\n",ans);
	}
	return 0;
}
