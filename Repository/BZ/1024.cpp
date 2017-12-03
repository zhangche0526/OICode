#include<iostream>
#include<cstdio>

int x,y,n;

double dfs(int lv,double x,double y)
{
	if(lv==1) return std::max(x/y,y/x);
	double res=1e60;
	for(int i=1;i<=lv/2;i++)
	{
		double nx=x*i/lv,ny=y*i/lv;
		res=std::min(res,std::max(dfs(i,nx,y),dfs(lv-i,x-nx,y)));
		res=std::min(res,std::max(dfs(i,x,ny),dfs(lv-i,x,y-ny)));
	}
	return res;
}

int main()
{
	scanf("%d%d%d",&x,&y,&n);
	printf("%.6f\n",dfs(n,x,y));
	return 0;
}
