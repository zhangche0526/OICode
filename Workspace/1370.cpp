#include<iostream>
#include<cstdio>

const int MAXN=2e3+5;

int fa[MAXN];
int findAnc(int x){return fa[x]==x?x:fa[x]=findAnc(fa[x]);}
void merge(int x,int y){x=findAnc(x),y=findAnc(y);if(x!=y) fa[x]=y;}

int main()
{
	int i;
	int n,m;scanf("%d%d",&n,&m);
	for(i=1;i<=n<<1;i++) fa[i]=i;
	while(m--)
	{
		char s[MAXN];scanf("%s",s);
		int x,y;scanf("%d%d",&x,&y);	
		if(s[0]=='F') merge(x,y);
		else merge(x,y+n),merge(x+n,y);
	}
	static bool vis[MAXN];
	int ans=0;
	for(i=1;i<=n;i++)
		if(!vis[findAnc(i)]) vis[fa[i]]=true,ans++;
	printf("%d",ans);
	return 0;
}
