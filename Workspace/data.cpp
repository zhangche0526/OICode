#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

double randPct(){return (double)rand()/32767;}
int randInt(int l,int r){return randPct()*(r-l+1)+l;}

int main()
{
	freopen("a.in","w",stdout);
	int i;
	int T=50;printf("%d\n",T);
	while(T--)
	{
		int a=randInt(900,1000),b=randInt(1,a);
		printf("%d %d\n",a,b);
	}
	return 0;
}
