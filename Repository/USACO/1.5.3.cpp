/*
TASK:sprime
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

int N;

bool isPri(int x)
{
	if(x==1) return false;
	int i;
	bool res=true;
	for(i=2;i<=sqrt(x);i++)
		if(x%i==0)
		{
			res=false;
			break;
		}
	return res;
}

void dfs(int num,int p)
{
	int i;
	if(p==N+1)
		printf("%d\n",num);
	else for(i=1;i<10;i++)
		if(isPri(num*10+i))
			dfs(num*10+i,p+1);
}

int main()
{
	freopen("sprime.in","r",stdin);
	freopen("sprime.out","w",stdout);
	scanf("%d",&N);
	dfs(0,1);
	return 0;
}
