#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int T,k;
int tgt[5][5]=
{
	{1,1,1,1,1},
	{0,1,1,1,1},
	{0,0,2,1,1},
	{0,0,0,0,1},
	{0,0,0,0,0}
};
int xm[8]={1,1,-1,-1,2,2,-2,-2};
int ym[8]={2,-2,2,-2,1,-1,1,-1};
int ok=0;
int jud(int mp[5][5])
{
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(tgt[i][j]!=mp[i][j])return 0;
	return 1;
}
int eva(int lv,int mp[5][5])
{
	int v=0;
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			if(mp[i][j]!=tgt[i][j])
			{
				v++;
				if(v+lv>k) return false;
			}
	return true;
}
void dfs(int lv,int mp[5][5],int x,int y)
{
	if(lv==k){if(jud(mp))ok=1;return;}
	if(ok==1)return;
	for(int i=0;i<8;i++)
	{
		int rx=x+xm[i],ry=y+ym[i];
		if(rx<0||rx>4||ry<0||ry>4)continue;
		swap(mp[x][y],mp[rx][ry]);
		if(eva(lv,mp)) dfs(lv+1,mp,rx,ry);
		swap(mp[x][y],mp[rx][ry]);
	}
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int mp[5][5];int x,y;
		ok=false;
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
			{
				char c;
				do c=getchar();
				while(c!='*'&&c!='1'&&c!='0');
				if(c=='*') {mp[i][j]=2;x=i;y=j;}
				else if(c=='1') mp[i][j]=1;
				else mp[i][j]=0;
			}
		for(k=1;k<=15;k++)
		{
			dfs(0,mp,x,y);
			if(ok)
			{
				printf("%d\n",k);
				break;
			}
		}
		if(!ok)printf("-1\n");
	}
	return 0;
}
