/*
ID:zhangch33
LANG:C++
TASK:gift1
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int MAXN=10,MAXL=14;
char name[MAXN+1][MAXL+1];
int hash[MAXN+1];
int money[MAXN+1];
int N;
int bkdrhash(char * x)
{
	int res=0;
	int seed1=998244353,seed2=1331;
	int P=1e9+7;
	for(int i=0;i<strlen(x);i++)
		res+=(res*seed1+x[i]*seed2)%P;
	return res;
}
int getid(char * x)
{
	for(int id=1;id<=N;id++)
		if(bkdrhash(x)==hash[id])
			return id;
}
int main()
{
	freopen("gift1.in","r",stdin);
	freopen("gift1.out","w",stdout);
	int i;
	cin>>N;
	for(i=1;i<=N;i++) cin>>name[i];
	for(i=1;i<=N;i++) hash[i]=bkdrhash(name[i]);
	char rname[MAXL+1];
	while(cin>>rname)
	{
		int aom,nop;
		scanf("%d%d",&aom,&nop);
		if((!aom)||(!nop))
		{
			for(i=1;i<=nop;i++) cin>>rname;
			continue;
		}
		money[getid(rname)]+=aom%nop-aom;
		int rmoney=aom/nop;
		for(i=1;i<=nop;i++)
		{
			cin>>rname;
			money[getid(rname)]+=rmoney;
		}
	}
	for(i=1;i<=N;i++)
		printf("%s %d\n",name[i],money[i]);
	return 0;
}
