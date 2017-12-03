/*
ID:zhangch33
LANG:C++
TASK:dualpal
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int N,S;
char num[100];

int main()
{
	freopen("dualpal.in","r",stdin);
	freopen("dualpal.out","w",stdout);
	int i,j;
	scanf("%d%d",&N,&S);
	int tot=0;
	for(i=S+1;tot<N;i++)
	{
		bool ok=false;
		for(int cnt=0,B=2;B<=10;B++)
		{
			memset(num,0,sizeof(num));
			int len=0,x=i;
			for(j=1;j<=x;j*=B) len++;
			if(x>j) len++;
			for(j=len-1;j>=0;j--,x/=B)
				num[j]=(x%B<10)?(x%B)+'0':x%B-10+'A';
			bool isSq=true;
			for(j=0;j<strlen(num)/2;j++)
				if(num[j]!=num[strlen(num)-j-1])
				{
					isSq=false;
					break;
				}
			if(isSq) cnt++;
			if(cnt>=2)
			{
				ok=true;
				break;
			}
		}
		if(ok)
		{
			tot++;
			printf("%d\n",i);
		}
	} 
	return 0;
}
