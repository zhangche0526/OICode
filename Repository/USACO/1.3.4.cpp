/*
ID:zhangch33
TASK:combo
LANG:C++
*/
#include<iostream>
#include<cstdio>
using namespace std;

int N;
int num[2][3];
int innum[3][101];
int cnt[3];

int main()
{
	freopen("combo.in","r",stdin);
	freopen("combo.out","w",stdout);
	int i,j,k,l;
	scanf("%d",&N);
	for(i=0;i<2;i++) 
		for(j=0;j<3;j++) 
			scanf("%d",&num[i][j]);
	int ans=N>=5?250:2*N*N*N;
	for(i=0;i<2;i++)
		for(j=0;j<3;j++)
		{
			int x=num[i][j];
			for(k=x,l=0;l<=2;l++,k=k==N?1:k+1)
				++innum[j][k];
			for(k=x==1?N:x-1,l=1;l<=2;l++,k=k==1?N:k-1)
				++innum[j][k];
		}
	for(i=0;i<3;i++)
		for(j=1;j<=N;j++)
			if(innum[i][j]>1) ++cnt[i];
	int res=1;
	for(i=0;i<3;i++) res*=cnt[i];
	ans-=res;
	printf("%d\n",ans);
	return 0;
}
