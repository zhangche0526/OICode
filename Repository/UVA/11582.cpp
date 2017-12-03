#include<iostream>
#include<cstdio>
using std::cin;
using std::cout;
using std::endl;
typedef unsigned long long ull;
const int MAXN=1005;

ull a,b;
int n,lp;
int fib[MAXN*MAXN];

int qpow(int x,ull y)
{
	int res=1;
	for(ull i=1;i<=y&&i;i<<=(ull)1,x=(ull)x*x%lp)
		if(i&y) res=(ull)res*x%lp;
	return res;
}

int main()
{
	fib[0]=0,fib[1]=1;
	int T;cin>>T;
	while(T--)
	{
		int i;
		cin>>a>>b>>n;
		if(a==0||n==1) {cout<<0<<endl;continue;}
		for(i=2;;i++)
		{
			fib[i]=(fib[i-1]+fib[i-2])%n;
			if(fib[i]==1&&fib[i-1]==0)
			{
				lp=i-1;
				break;
			}
		}
		int x=a%(ull)lp;
		int pos=qpow(x,b);
		cout<<fib[pos]<<endl;
	}
	return 0;
}
