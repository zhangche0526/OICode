#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	int i,j;
	int N,M;
	N=1+rand()%1000;M=1+rand()%1000;
	printf("%d %d\n",N,M);
	for(i=1;i<=N;i++)
	{
		for(j=1;j<M;j++)
			printf("%d ",1+rand()%100);
		printf("\n");
	}
	for(i=1;i<N;i++)
	{
		for(j=1;j<=M;j++)
			printf("%d ",1+rand()%100);
		printf("\n");
	}
	for(i=1;i<N;i++)
	{
		for(j=1;j<M;j++)
			printf("%d ",1+rand()%100);
		printf("\n");
	}
	return 0;
}
