/*
TASK:milk3
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
using namespace std;
int A,B,C;
bool vis[21][21];
int ans[21],acnt;

void dfs(int x,int y)//x:recent A; y:recent B
{
	if(vis[x][y]) return;
	vis[x][y]=true;
	dfs(0,y);//B->C
	dfs(x,0);//A->C
	if(x>B-y) dfs(x-(B-y),B);//A->B
	else dfs(0,x+y);
	if(y>A-x) dfs(A,y-(A-x));//B->A
	else dfs(x+y,0);
	int z=C-(x+y);
	if(z>A-x) dfs(A,C-A-(z-(A-x)));//C->A
	else dfs(x+z,C-(x+z));
	if(z>B-y) dfs(C-B-(z-(B-y)),B);//C->B
	else dfs(C-(y+z),y+z);
}
int main()
{
	freopen("milk3.in","r",stdin);
	freopen("milk3.out","w",stdout);
	int i;
	scanf("%d%d%d",&A,&B,&C);
	dfs(0, 0);
	for(i=C;i>=0;i--)
		if(vis[0][i])
			ans[acnt++]=C-i;
	for(i=0;i<acnt-1;i++)
		printf("%d ",ans[i]);
	printf("%d\n",ans[acnt-1]);
}
