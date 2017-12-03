#include<iostream>
#include<cstdio>
#include<cmath>

bool check(double a,double b,double r1,double r2)
{
	if(a>b) std::swap(a,b);
	if(r1>r2) std::swap(r1,r2);
	if(a<r2*2) return false;
	double z=r1+r2,
		   x=a-z,
		   y=b-z;
	return x*x+y*y>=z*z;
}

int main()
{
	double a,b,r1,r2;
	while(scanf("%lf%lf%lf%lf",&a,&b,&r1,&r2)!=EOF)
	{
		if(check(a,b,r1,r2)) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
