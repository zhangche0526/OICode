#include<iostream>
#include<cstdio>

const int MAXN=3e4+5;

int N;
int f[MAXN];

int abs(int x){return x<0?-x:x;}

bool check(int t)
{
	int i,curf=1,curt=0;
	for(i=1;i<=N;i++)
	{
		if((f[i]-1)*20<=t) continue;
		if(curt+abs(curf-f[i])*20<=t) continue;
		int det=0;
		while(true)
		{
			if(curt+(curf==1?0:10)+4*(f[i]+det-curf)+det*20<=t)
				det++;
			else break;
		}
		if(!det) return false;
		curt+=(curf==1?0:10)+4*(f[i]+det-1-curf);
		curf=f[i]+det-1;
	}
	return true;
}

int main()
{
	while(scanf("%d",&N)!=EOF&&N)
	{
		for(int i=1;i<=N;i++) scanf("%d",&f[i]);
		int l=0,r=f[N]*20,mid;
		while(l<r)
		{
			mid=l+r>>1;
			if(check(mid)) r=mid;
			else l=mid+1;
		}
		printf("%d\n",l);
	}
	return 0;
}
