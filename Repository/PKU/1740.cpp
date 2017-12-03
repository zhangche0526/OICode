#include<iostream>
#include<cstdio>
#include<algorithm>

const int MAXN=15;

int N;

int main()
{
	while(scanf("%d",&N)!=EOF&&N)
	{
		int i,j,x;
        int xorSum=0;
		for(i=1;i<=N;i++) scanf("%d",&x),xorSum^=x;
		if(!xorSum) printf("0\n");
		else printf("1\n");
	}
	return 0;
}

