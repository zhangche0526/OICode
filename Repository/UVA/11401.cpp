#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int MAXN=1e6;

ll f[MAXN+5];
inline void preTab()
{
	for(ll i=4;i<=MAXN;i++) 
		f[i]=f[i-1]+((i-1)*(i-2)/2-(i-1)/2)/2;
}
int main()
{
	preTab();
	int n;
	while(cin>>n)
	{
		if(n<3) break;
		cout<<f[n]<<endl;
	}
	return 0;
}
