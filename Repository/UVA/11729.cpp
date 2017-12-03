#include<iostream>
#include<cstdio>
#include<algorithm>

const int MAXN=1e3+5;

int n;
struct T{int B,J;} tsk[MAXN];
bool cmp(const T &x,const T &y){return x.J>y.J;}

int main()
{
	int i,Case=0;
	while(~scanf("%d",&n)&&n)
	{
		for(i=1;i<=n;i++)
		{
			int B,J;scanf("%d%d",&B,&J);
			tsk[i]=(T){B,J};
		}
		std::sort(tsk+1,tsk+n+1,cmp);
		int sT=0,ans=0;
		for(i=1;i<=n;i++)
		{
			sT+=tsk[i].B;
			ans=std::max(ans,sT+tsk[i].J);
		}
		printf("Case %d: %d\n",++Case,ans);
	}
	return 0;
}
