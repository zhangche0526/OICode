#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN=50005;

int N,K;

inline int calRela(int x,int y)
{return x==y?-x:x+y;}

int fa[MAXN],rela[MAXN];
int calAnc(int x)
{
	int xFa=fa[x];
	if(xFa==x) return x;
	fa[x]=calAnc(xFa);
	rela[x]=calRela(rela[x],rela[xFa]);
	return fa[x];
}

void join(int t,int x,int y)
{
	int xAnc=calAnc(x),yAnc=calAnc(y);
	if(xAnc==yAnc) return;
	fa[xAnc]=yAnc;
	rela[xAnc]=calRela(calRela(t,rela[y]),-rela[x]);
}

int main()
{
	freopen("eat.in","r",stdin);
	freopen("eat.out","w",stdout);
	int i,ans=0;
	scanf("%d%d",&N,&K);
	for(i=1;i<=N;i++) fa[i]=i;
	for(i=1;i<=K;i++)
	{
		int t,u,v;scanf("%d%d%d",&t,&u,&v);
		if(u>N||v>N) {++ans;continue;}
		if(t==2&&u==v) {++ans;continue;}
		if(calAnc(u)==calAnc(v))
		{
			if(t==2&&calRela(rela[u],-rela[v])!=1)
				++ans;
			else if(t==1&&rela[u]!=rela[v])
				++ans;
		}else join(t-1,u,v);
	}
	printf("%d\n",ans);
	return 0;
}
