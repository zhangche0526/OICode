#include<cstdio>
int main()
{
	double a,b,c;
	while(scanf("%lf%lf%lf",&a,&b,&c)!=EOF)
		printf("%.5lf\n",b*(a+b-1)/(a+b)/(a+b-c-1));
	return 0;
}
