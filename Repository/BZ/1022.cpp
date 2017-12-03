#include<iostream>
#include<cstdio>

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		int n,i,xorsum=0;bool allone=false;
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			int x;scanf("%d",&x);
			xorsum^=x;
			if(x>1) allone=1;
		}
		if(!xorsum^allone) printf("John\n");
		else printf("Brother\n");
	}
	return 0;
}
