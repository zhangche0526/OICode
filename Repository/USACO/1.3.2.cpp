/*
ID:zhangch33
LANG:C++
TASK:barn1
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXS=200;

int M,S,C;
int stall[MAXS+1],space[MAXS];

bool cmp(const int & a,const int & b){return a>b;}

int main()
{
	freopen("barn1.in","r",stdin);
	freopen("barn1.out","w",stdout);
	int i;
	scanf("%d%d%d",&M,&S,&C);
	for(i=1;i<=C;i++) scanf("%d",&stall[i]);
	sort(stall+1,stall+C+1);
	for(i=1;i<C;i++) space[i]=stall[i+1]-stall[i]-1;
	sort(space+1,space+C,cmp);
	int ans=stall[C]-stall[1]+1;
	for(i=1;i<M;i++) ans-=space[i];
	printf("%d\n",ans);
	
}
