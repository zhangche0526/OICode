#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using std::min;

int N,M,S,T;
int W[MAXN];

int main()
{
	int i;scanf("%d%d%d%d",&N,&M,&S,&T);
	for(i=1;i<=N;i++) scanf("%d",W+i);
	for(i=1;i<=M;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		addEdge();
	}
	return 0;
}
