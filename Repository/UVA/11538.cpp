#include<iostream>
#include<cstdio>
using namespace std;
typedef unsigned long long ull;

int main()
{
	ull n,m;
	while(cin>>n>>m)
	{
		if(!n&&!m) break;
		if(n>m) swap(n,m);
		cout<<n*m*(m+n-2)+2*n*(n-1)*(3*m-n-1)/3<<endl;
	}
	return 0;
}
