/*
ID:zhangch33
TASK:ariprog
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int N,M;
bool inS[130000];
bool noans=true;

struct A{int a,b;} ans[10000];int acnt;

bool cmp(const A & l,const A & r)
{
	if(l.b==r.b) return l.a<r.a;
	return l.b<r.b;
}

int main()
{
	freopen("ariprog.in","r",stdin);
	freopen("ariprog.out","w",stdout);
	int i,j,k;
	scanf("%d%d",&N,&M);
	for(i=0;i<=M;i++)
		for(j=0;j<=M;j++)
			inS[i*i+j*j]=true;
	for(i=0;i<=M*M*2;i++)
	if(inS[i])
		for(j=1;i+(N-1)*j<=M*M*2;j++)
		{
			bool yes=true;
			for(k=1;k<N;k++) 
				if(!inS[i+j*k]) 
				{
					yes=false;
					break;
				}
			if(yes)
			{
				ans[acnt++]=(A){i,j};
				noans=false;
			}
		}
	sort(ans,ans+acnt,cmp);
	for(i=0;i<acnt;i++)
		printf("%d %d\n",ans[i].a,ans[i].b);
	if(noans) printf("NONE\n");
	return 0;
}
