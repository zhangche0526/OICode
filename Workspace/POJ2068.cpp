#include<iostream>
#include<cstdio>
#include<cstring>

const int MAXN=11,MAXM=1<<13|5;

int n,m;
int B[2][MAXN];

bool f[MAXM][2][MAXN];
bool calc()
{
	int i,t,a,b;
	memset(f,false,sizeof f);
	memset(f[0],true,sizeof f[0]);
	for(a=1;a<=m;a++)
		for(t=0;t<2;t++) for(i=0;i<n;i++)
		{
			int nt=t^1,ni=t?(i+1)%n:i;
			for(b=1;b<=B[t][i]&&b<=a;b++)
				f[a][t][i]|=!f[a-b][nt][ni];
		}
	return f[m][0][0];
}

int main()
{
	int i;
	while(scanf("%d",&n)&&n)
	{
		scanf("%d",&m);
		for(i=0;i<n;i++) scanf("%d%d",B[0]+i,B[1]+i);
		puts(calc()?"1":"0");
	}
	return 0;
}
