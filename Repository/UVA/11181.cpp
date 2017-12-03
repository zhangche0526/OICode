#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=25;

int n,r;bool buy[MAXN];
double P[MAXN],sum[MAXN],tot;

void dfs(int lv,int num,double p)
{
	if(num>r||lv-1-num>n-r) return; 
	if(lv>n)
	{
		tot+=p;
		for(int i=1;i<=n;i++) if(buy[i]) 
			sum[i]+=p;
		return;
	}
	buy[lv]=false;dfs(lv+1,num,p*(1-P[lv]));
	buy[lv]=true;dfs(lv+1,num+1,p*P[lv]);
}

int main()
{
	int Case=0;
	while(~scanf("%d%d",&n,&r)&&n)
	{
		int i;
		memset(sum,0,sizeof(sum));tot=0;
		for(i=1;i<=n;i++) scanf("%lf",P+i);
		dfs(1,0,1.0);
		printf("Case %d:\n",++Case);
		for(i=1;i<=n;i++) printf("%.6lf\n",sum[i]/tot);
	}
	return 0;
}
