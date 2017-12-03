/*
ID:zhangch33
LANG:C++
TASK:milk
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#define min(a,b) (a<b?a:b)
using namespace std;

const int MAXM=5000;

int N,M;

struct F{int P,A;} farmer[MAXM+1];

bool cmp(const F & a,const F & b){return a.P<b.P;}

int main()
{
	freopen("milk.in","r",stdin);
	freopen("milk.out","w",stdout);
	int i;
	scanf("%d%d",&N,&M);
	for(i=1;i<=M;i++) scanf("%d%d",&farmer[i].P,&farmer[i].A);
	sort(farmer+1,farmer+M+1,cmp);
	int ans=0;
	for(i=1;i<=M&&N;i++)
	{
		ans+=min(N,farmer[i].A)*farmer[i].P;
		N-=min(N,farmer[i].A);
	}
	printf("%d\n",ans);
}
