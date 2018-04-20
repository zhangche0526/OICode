#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
typedef long long ll;

const int MAXN=1e6;

int randint(int l,int r){return ((ll)rand()*rand()*rand()+rand()*rand()+rand())%(r-l+1)+l;}

int main()
{
	freopen("data.in","w",stdout);
	int i;srand(time(0));
	int n=randint(1,MAXN);
	for(i=1;i<=n;i++) printf("%d",randint(!i,9));puts("");
	for(i=1;i<=n;i++) printf("%d",randint(!i,9));
}
