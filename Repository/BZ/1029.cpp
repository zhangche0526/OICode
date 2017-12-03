#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>

const int MAXN=15e4+5;

int n;

struct T{int t,ddl;} task[MAXN];

bool operator <(T a,T b){return a.ddl<b.ddl;}

std::priority_queue<int,std::vector<int>,std::less<int> > heap;

int main()
{
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d%d",&task[i].t,&task[i].ddl);
	std::sort(task+1,task+n+1);
	int rT=0,ans=0;
	for(i=1;i<=n;i++)
		if(rT+task[i].t<=task[i].ddl)
		{
			ans++;
			rT+=task[i].t;
			heap.push(task[i].t);
		}else
		{
			int tp=heap.top();
			if(task[i].t<tp)
			{
				heap.pop();
				heap.push(task[i].t);
				rT=rT-tp+task[i].t;
			}
		}
	printf("%d\n",ans);
	return 0;
}
