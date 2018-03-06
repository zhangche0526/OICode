#include<iostream>
#include<cstdio>

int fa[102] , d[102];
int findAnc(int x)
{
	if(x==fa[x]) return x;
	int f=findAnc(fa[x]);
	d[x]+=d[fa[x]];
	return fa[x]=f;
}
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<=n+1;i++) fa[i]=i,d[i]=0;
		bool gg=false;
		while(m--)
		{
			int l,r,v;scanf("%d%d%d",&l,&r,&v);r++;
			int fl=findAnc(l),fr=findAnc(r);
			if(fl!=fr)
			{
				fa[fl]=fr;
				d[fl]=v+d[r]-d[l];
			}
			else if(d[l]-d[r]!=v) gg=true;
		}
		puts(gg?"false":"true");
	}
	return 0;
}
