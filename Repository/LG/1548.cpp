#include<iostream>
#include<cstdio>

int main()
{
	int i,j,n,m,ans1=0,ans2=0;
	scanf("%d%d",&n,&m);
	int a=std::min(n,m);
	for(i=1;i<=n;i++) ans1+=(n+1-i)*(m+1-i);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(i!=j) ans2+=(n+1-i)*(m+1-j);
	printf("%d %d\n",ans1,ans2);
	return 0;
}
