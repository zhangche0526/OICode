#include<iostream>
#include<cstdio>

int main()
{
	int i;
	double ans=0,t=1,s=-1;
	for(i=1;i<=10;i++)
	{
		t*=2.0,s+=8;
		ans+=s/t;
		printf("%lf\n",ans);
	}
	return 0;
}
