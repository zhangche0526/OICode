#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
using namespace std;

const int MAXN=1e6;
const int n=1e6,m=1e6;

char s1[MAXN][105],s2[MAXN][105];

void genstr(char *s,int sL)
{
	for(int i=0;i<sL;i++) s[i]=rand()%26+'a';
}

int qry[MAXN];

int main()
{
	freopen("hashTree.in","w",stdout);
	int i;srand(time(0));
	printf("%d %d\n",n,m);
	for(i=1;i<=n;i++)
	{
		genstr(s1[i],rand()%100+1);
		genstr(s2[i],rand()%100+1);
		printf("%s %s\n",s1[i],s2[i]);
	}
	for(i=1;i<=n;i++)
	{
		qry[i]=rand()%n+1;
		printf("%s\n",s1[i]);
	}
	freopen("hashTree.ans","w",stdout);
	for(i=1;i<=n;i++) printf("%s\n",s2[i]);
	return 0;
}
