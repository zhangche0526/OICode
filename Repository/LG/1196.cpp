#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int N=30005;

int T;

int fa[N],dis[N],size[N];

int calAnc(int x)
{
	if(fa[x]==x) return x;
	int xFa=fa[x];
	int res=calAnc(xFa);
	fa[x]=res;
	dis[x]+=dis[xFa];
	return res;
}

int main()
{
	freopen("galaxy.in","r",stdin);
	freopen("galaxy.out","w",stdout);
	scanf("%d",&T);
	int i;
	for(i=1;i<=N;i++)
		fa[i]=i,size[i]=1;
	while(T--)
	{
		char c;do c=getchar();while(c!='M'&&c!='C');
		int x,y;scanf("%d%d",&x,&y);
		int xAnc=calAnc(x),yAnc=calAnc(y);
		if(c=='M')
		{
			fa[xAnc]=yAnc;
			dis[xAnc]=size[yAnc];
			size[yAnc]+=size[xAnc];
		}else
		{
			int ans;
			if(xAnc!=yAnc) ans=-1;
			else ans=abs(dis[y]-dis[x])-1;
			printf("%d\n",ans);
		}
	}
}
