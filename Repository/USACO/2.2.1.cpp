/*
ID:zhangch33
TASK:preface
LANG:C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const char rnum[4][9][5]=
{
	{"I","II","III","IV","V","VI","VII","VIII","IX"},
	{"X","XX","XXX","XL","L","LX","LXX","LXXX","XC"},
	{"C","CC","CCC","CD","D","DC","DCC","DCCC","CM"},
	{"M","MM","MMM"}
};
const char num[8]="IVXLCDM";
int ans[200];

int N;

int main()
{
	freopen("preface.in","r",stdin);
	freopen("preface.out","w",stdout);
	int i,j,k,l;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
	{
		int x=i;
		for(j=0;x;x/=10,j++)
		{
			for(k=0;k<strlen(rnum[j][x%10-1]);k++)
			{
				char c=rnum[j][x%10-1][k];
				if(x%10) ++ans[c];
			}
		} 
	}
	for(i=0;i<7;i++)
		if(ans[num[i]])
			printf("%c %d\n",num[i],ans[num[i]]);
	return 0;
}
