/*
ID:zhangch33
TASK:runround
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int numa[100];
bool vis[100];
bool check(int x)
{
	int i;
	for(i=0;x;i++,x/=10)
	{
		if(!(x%10)) return false;
		numa[i]=x%10;
	}
	memset(vis,false,sizeof(vis));
	int lftnum=i+1,rp=i,len=i+1;
	for(;i>=0;i--) 
		if(vis[numa[i]]) return false;
		else vis[numa[i]]=true;
	memset(vis,false,sizeof(vis));
	vis[rp]=true;
	while(lftnum!=0)
	{
		rp=i-(numa[rp]%len);
		if(vis[rp]) return false;
		--lftnum;
		vis[rp]=true;
	}
	if(rp==len-1) return true;
	return false;
}

int main()
{
	freopen("runround.in","r",stdin);
	freopen("runround.out","w",stdout);
	int i;
	int num;scanf("%d",&num);
	for(i=num+1;;i++)
		if(check(i))
		{
			printf("%d",i);
			break;
		}
	return 0;
}
