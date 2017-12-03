#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	int e=c-a,f=d-b;
	if(f<0) f+=60,e--;
	printf("%d %d\n",e,f);
	return 0;
}
