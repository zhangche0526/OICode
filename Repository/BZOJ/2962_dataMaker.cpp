#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;
const int N=1000,Q=1000;

int randInt(int l,int r){return l+rand()%(r-l+1);}

int main()
{
	freopen("data.in","w",stdout);
	int i;
	srand(time(0));
	printf("%d %d\n",N,Q);
	for(i=1;i<=N;i++) printf("%d ",randInt(1,12345));putchar('\n');
	for(i=1;i<=Q;i++)
	{
		int typ=randInt(0,2);
		int l,r;l=randInt(1,N-1),r=randInt(l+1,N);
		switch(typ)
		{
			case 0:printf("I %d %d %d\n",l,r,randInt(1,12345));break;
			case 1:printf("R %d %d\n",l,r);break;
			case 2:printf("Q %d %d %d\n",l,r,randInt(1,min(20,r-l+1)));break;
		}
	}
	return 0;
}

