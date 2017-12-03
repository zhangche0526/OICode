/*
TASK:holstein
ID:zhangch33
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXV=25,MAXG=15;

int V,G;
bool chosed[MAXG+1];

struct P{int num,c[MAXG+1],ftn;} p[1<<MAXG+1];int pcnt;
bool cmp(const P & a,const P & b)
{
	if(a.num==b.num) return a.ftn<b.ftn;
	return a.num<b.num;
}

int w[MAXG+1][MAXV+1];
int v[MAXV+1];
void dfs(int x,int cnt)
{
	int i;
	bool ok=true;
	for(i=1;i<=V;i++) if(v[i]>0) {ok=false;break;}
	if(ok)
	{
		p[++pcnt].num=cnt;
		for(i=1;i<=G;i++) p[pcnt].c[i]=chosed[i];
		return;
	}
	if(x>G) return;
	dfs(x+1,cnt);
	chosed[x]=true;
	int rv[MAXV+1];
	for(i=1;i<=V;i++) rv[i]=v[i]; 
	for(i=1;i<=V;i++) v[i]-=w[x][i],v[i]=v[i]<0?0:v[i];
	dfs(x+1,cnt+1);
	for(i=1;i<=V;i++) v[i]=rv[i]; 
	chosed[x]=false;
}

int main()
{
	freopen("holstein.in","r",stdin);
	freopen("holstein.out","w",stdout);
	int i,j;
	scanf("%d",&V);
	for(i=1;i<=V;i++)
		scanf("%d",&v[i]);
	scanf("%d",&G);
	for(i=1;i<=G;i++)
		for(j=1;j<=V;j++)
			scanf("%d",&w[i][j]);
	dfs(1,0);
	for(i=1;i<=pcnt;i++) 
		for(j=1;j<=G;j++)
			if(p[i].c[j])
				p[i].ftn+=j;
	sort(p+1,p+pcnt+1,cmp);
	printf("%d ",p[1].num);
	vector<int> ans;
	for(i=1;i<=G;i++) if(p[1].c[i]) ans.push_back(i);
	for(i=0;i<ans.size()-1;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[ans.size()-1]);
	return 0;
}

