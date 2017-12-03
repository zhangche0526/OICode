#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN=100,MAXM=50*99,INF=1<<30;

struct node2{int u,v,w;} a[MAXM+1];int acnt;
void add2(int u,int v,int w){++acnt,a[acnt].u=u,a[acnt].v=v,a[acnt].w=w;}

int fa[MAXN+1];
int getfa(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}

void join(int x,int y)
{
	fa[getfa(x)]=getfa(y);
}

bool cmp(const node2 & a,const node2 & b){return a.w<b.w;}

int N,M;

int main()
{
	int i;
	while(cin>>N>>M&&N)
	{
		acnt=0;
		for(i=1;i<=N;i++) fa[i]=i;
		for(i=1;i<=M;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			add2(u,v,w);
		}sort(a+1,a+M+1,cmp);
		int L,R;
		int minv=INF;
		for(L=1;L<=M-(N-1)+1;L++)
		{
			for(i=1;i<=N;i++) fa[i]=i;
			int times=0;
			for(R=L;R<=M;R++)
				if(getfa(a[R].u)!=getfa(a[R].v))
				{
					join(a[R].u,a[R].v);
					++times;
					if(times==N-1)
					{
						minv=min(minv,a[R].w-a[L].w);
						break;
					}
				}
		}
		if(minv==INF) cout<<-1<<endl;
		else cout<<minv<<endl;
	}
	return 0;
}
