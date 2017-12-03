/*
ID:zhangch33
LANG:C++
TASK:palsquare
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int B;
char num[100],snum[100];

int main()
{
	freopen("palsquare.in","r",stdin);
	freopen("palsquare.out","w",stdout);
	int i,j;
	scanf("%d",&B);
	for(i=1;i<=300;i++)
	{
		memset(num,0,sizeof(num));
		memset(snum,0,sizeof(snum));
		int len=0,x=i*i;
		for(j=1;j<=x;j*=B) len++;
		if(x>j) len++;
		for(j=len-1;j>=0;j--,x/=B)
			snum[j]=(x%B<10)?(x%B)+'0':x%B-10+'A';
		bool isSq=true;
		for(j=0;j<strlen(snum)/2;j++)
			if(snum[j]!=snum[strlen(snum)-j-1])
			{
				isSq=false;
				break;
			}
		if(isSq)
		{
			len=0,x=i;
			for(j=1;j<=x;j*=B) len++;
			if(x>j) len++;
			for(j=len-1;j>=0;j--,x/=B)
				num[j]=(x%B<10)?(x%B)+'0':x%B-10+'A';
			printf("%s %s\n",num,snum);
		}
	}	
	return 0;
}
