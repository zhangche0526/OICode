#include<iostream>
#include<cstdio>
#include<vector>
using std::vector;

const int MAXN=6000;

bool visot[MAXN],vismy[MAXN];

vector<int> otonly,myonly,both;

int main()
{
	FILE *ot=fopen("ot.txt","r");
	FILE *my=fopen("my.txt","r");
	int i,x;
	while(~fscanf(ot,"%d",&x)) visot[x]=true;
	while(~fscanf(my,"%d",&x)) vismy[x]=true;
	for(i=1000;i<MAXN;i++)
	{
		if(visot[i] and vismy[i]) both.push_back(i);
		if(visot[i] xor vismy[i])
		{
			(visot[i]?otonly:myonly).push_back(i);
		}
	}
	printf("otonly %d\n",otonly.size());
	for(vector<int>::iterator i=otonly.begin();i!=otonly.end();i++)
		printf("%d ",*i);
	puts("");
	printf("myonly %d\n",myonly.size());
	for(vector<int>::iterator i=myonly.begin();i!=myonly.end();i++)
		printf("%d ",*i);
	puts("");
	printf("both %d\n",both.size());
	for(vector<int>::iterator i=both.begin();i!=both.end();i++)
		printf("%d ",*i);
	return 0;
}
